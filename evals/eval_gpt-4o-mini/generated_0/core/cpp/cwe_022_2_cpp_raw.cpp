#include <archive.h>
#include <archive_entry.h>
#include <string.h>
#include <iostream>
#include <filesystem>

bool extract_archive(struct archive *src, const char *dest_path) {
    struct archive *out;
    struct archive_entry *entry;
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_SECURE;
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

        // Ensure the path is secure
        if (std::filesystem::path(full_path).is_relative() ||
            full_path != std::filesystem::absolute(full_path).string()) {
            std::cerr << "Invalid path detected, skipping extraction." << std::endl;
            continue;
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
    struct archive *src;
    int r;

    // Check if destination path is a valid directory
    if (!std::filesystem::is_directory(dest_path)) {
        std::cerr << "Destination path is not a valid directory." << std::endl;
        return false;
    }

    // Create a new archive object
    src = archive_read_new();
    archive_read_support_format_tar(src);
    archive_read_support_format_zip(src); // Updated to avoid deprecated function

    // Open the tar file
    if ((r = archive_read_open_filename(src, tar_path.c_str(), 10240)) != ARCHIVE_OK) {
        std::cerr << "Could not open tar file: " << archive_error_string(src) << std::endl;
        archive_read_free(src);
        return false;
    }

    // Extract the archive
    bool result = extract_archive(src, dest_path.c_str());

    // Free the archive object
    archive_read_free(src);
    return result;
}