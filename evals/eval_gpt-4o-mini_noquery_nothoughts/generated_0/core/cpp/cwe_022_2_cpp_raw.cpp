#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <iostream>
#include <filesystem>

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

        // Prevent directory traversal vulnerabilities
        if (std::filesystem::path(full_path).is_absolute() || std::filesystem::path(full_path).parent_path() != std::filesystem::path(dest_path)) {
            std::cerr << "Directory traversal attempt detected: " << full_path << std::endl;
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
    return r == ARCHIVE_EOF;
}

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src;
    int r;

    // Check if destination path is a directory
    if (!std::filesystem::is_directory(dest_path)) {
        std::cerr << "Destination path is not a directory." << std::endl;
        return false;
    }

    // Open the tar file
    src = archive_read_new();
    archive_read_support_format_tar(src);
    archive_read_support_compression_all(src);
    if (archive_read_open_filename(src, tar_path.c_str(), 10240) != ARCHIVE_OK) {
        std::cerr << "Could not open tar file." << std::endl;
        archive_read_free(src);
        return false;
    }

    // Extract the archive
    bool result = extract_archive(src, dest_path.c_str());

    // Clean up
    archive_read_free(src);
    return result;
}