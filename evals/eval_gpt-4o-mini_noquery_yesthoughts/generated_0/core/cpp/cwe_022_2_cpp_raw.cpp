#include <archive.h>
#include <archive_entry.h>
#include <filesystem>
#include <string>
#include <iostream>

bool extract_archive(struct archive *src, const char *dest_path) {
    struct archive *out;
    struct archive_entry *entry;
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM;
    int r;
    char full_path[4096];

    // Initialize the archive writer
    out = archive_write_disk_new();
    if (!out) {
        return false;
    }
    archive_write_disk_set_options(out, flags);

    // Read and extract each entry
    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        // Create full path
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        // Validate extracted path to prevent directory traversal
        std::filesystem::path extracted_path(full_path);
        std::filesystem::path dest(dest_path);
        if (extracted_path.lexically_relative(dest).empty() || extracted_path.string().find("..") != std::string::npos) {
            std::cerr << "Potential directory traversal detected: " << full_path << std::endl;
            archive_write_free(out);
            return false;
        }

        // Write header
        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            return false;
        }

        // Copy data
        const void *buff;
        size_t size;
        la_int64_t offset;
        while ((r = archive_read_data_block(src, &buff, &size, &offset)) == ARCHIVE_OK) {
            if (archive_write_data_block(out, buff, size, offset) != ARCHIVE_OK) {
                archive_write_free(out);
                return false;
            }
        }
        if (r != ARCHIVE_EOF) {
            archive_write_free(out);
            return false;
        }
    }

    archive_write_free(out);
    return r == ARCHIVE_EOF ? true : false;
}

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    // Validate the destination path
    if (!std::filesystem::exists(dest_path) || !std::filesystem::is_directory(dest_path)) {
        std::cerr << "Invalid destination path." << std::endl;
        return false;
    }

    // Open the tar file
    struct archive *src = archive_read_new();
    if (!src) {
        return false;
    }

    // Support for tar format
    archive_read_support_format_tar(src);
    archive_read_support_compression_all(src);

    // Open the tar file
    if (archive_read_open_filename(src, tar_path.c_str(), 10240) != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Extract the archive
    bool result = extract_archive(src, dest_path.c_str());

    // Clean up
    archive_read_free(src);
    return result;
}