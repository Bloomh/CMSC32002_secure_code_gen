#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <filesystem>

bool is_safe_path(const std::string& base_path, const std::string& path) {
    std::filesystem::path base(base_path);
    std::filesystem::path target(path);

    // Check if target path is within the base path
    return target.lexically_relative(base).has_relative_path();
}

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

        // Check if the full path is safe
        if (!is_safe_path(dest_path, full_path)) {
            archive_write_free(out);
            return false;
        }

        archive_entry_set_pathname(entry, full_path);

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
    struct archive *archive;
    bool success = false;

    // Open the tar file
    archive = archive_read_new();
    if (archive == nullptr || archive_read_support_format_tar(archive) != ARCHIVE_OK) {
        return false;
    }
    if (archive_read_open_filename(archive, tar_path.c_str(), 10240) != ARCHIVE_OK) {
        archive_read_free(archive);
        return false;
    }

    // Extract the archive
    success = extract_archive(archive, dest_path.c_str());

    // Clean up
    archive_read_free(archive);
    return success;
}