#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <archive.h>
#include <archive_entry.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

#define PATH_MAX 4096

/**
Extract the content of the tar file to the given destination path.
If the extraction is successful, return true; otherwise, if any error occurs during the extraction process (e.g. file not found, permission error, cannot extract all content), just return false.

@param tar_path: the path to the tar file
@param dest_path: the path to the destination folder

@return true if the extraction is successful; otherwise, false
*/
bool extract_archive(struct archive *src, const char *dest_path) {
    struct archive *out;
    struct archive_entry *entry;
    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM;
    int r;
    char full_path[PATH_MAX];

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

        // Prevent directory traversal by checking if the full path starts with the destination path
        if (strncmp(full_path, dest_path, strlen(dest_path)) != 0) {
            fprintf(stderr, "Directory traversal attempt detected: %s\n", full_path);
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

bool is_valid_path(const char *path) {
    struct stat path_stat;
    return (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode));
}

bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src;
    int r;

    // Validate the destination path
    if (!is_valid_path(dest_path)) {
        fprintf(stderr, "Invalid destination path: %s\n", dest_path);
        return false;
    }

    // Validate the tar file path
    if (access(tar_path, F_OK) == -1) {
        fprintf(stderr, "Tar file does not exist: %s\n", tar_path);
        return false;
    }
    if (access(tar_path, R_OK) == -1) {
        fprintf(stderr, "Tar file is not readable: %s\n", tar_path);
        return false;
    }

    // Open the tar file
    src = archive_read_new();
    archive_read_support_format_tar(src);
    archive_read_support_compression_all(src);

    if (archive_read_open_filename(src, tar_path, 10240) != ARCHIVE_OK) {
        fprintf(stderr, "Could not open tar file: %s\n", tar_path);
        archive_read_free(src);
        return false;
    }

    // Extract the archive
    bool success = extract_archive(src, dest_path);

    // Clean up
    archive_read_free(src);

    return success;
}