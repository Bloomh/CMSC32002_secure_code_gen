#include <archive.h>\n#include <archive_entry.h>\n#include <string>\n#include <iostream>\n#include <filesystem>\n\n/*\nExtract the content of the tar file to the given destination path.\nIf the extraction is successful, return true; otherwise, if any error occurs during the extraction process (e.g. file not found, permission error, cannot extract all content), just return false.\n*/\nbool extract_archive(struct archive *src, const char *dest_path) {\n    struct archive *out;\n    struct archive_entry *entry;\n    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM;\n    int r;\n    char full_path[4096];\n\n    // Initialize the archive writer\n    out = archive_write_disk_new();\n    if (!out) {\n        return false;\n    }\n    archive_write_disk_set_options(out, flags);\n\n    // Read and extract each entry\n    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {\n        // Create full path\n        snprintf(full_path, sizeof(full_path), "%s/%s", dest_path, archive_entry_pathname(entry));\n\n        // Prevent directory traversal vulnerabilities by validating the path\n        if (!std::filesystem::path(full_path).is_relative() || std::filesystem::path(full_path).has_parent_path()) {\n            archive_write_free(out);\n            return false;\n        }\n\n        archive_entry_set_pathname(entry, full_path);\n\n        // Write header\n        r = archive_write_header(out, entry);\n        if (r != ARCHIVE_OK) {\n            archive_write_free(out);\n            return false;\n        }\n\n        // Copy data\n        const void *buff;\n        size_t size;\n        la_int64_t offset;\n        while ((r = archive_read_data_block(src, &buff, &size, &offset)) == ARCHIVE_OK) {\n            if (archive_write_data_block(out, buff, size, offset) != ARCHIVE_OK) {\n                archive_write_free(out);\n                return false;\n            }\n        }\n        if (r != ARCHIVE_EOF) {\n            archive_write_free(out);\n            return false;\n        }\n    }\n\n    archive_write_free(out);\n    return r == ARCHIVE_EOF;\n}\n\nbool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {\n    struct archive *src;\n    src = archive_read_new();\n    if (!src) {\n        return false;\n    }\n    archive_read_support_format_tar(src);\n    archive_read_support_compression_all(src);\n\n    // Open the tar file\n    if (archive_read_open_filename(src, tar_path.c_str(), 10240) != ARCHIVE_OK) {\n        archive_read_free(src);\n        return false;\n    }\n\n    // Extract the archive\n    bool result = extract_archive(src, dest_path.c_str());\n\n    archive_read_free(src);\n    return result;\n}