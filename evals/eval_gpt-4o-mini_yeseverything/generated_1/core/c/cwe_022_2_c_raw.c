#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <archive.h>
#include <archive_entry.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h> // Use the standard limits.h to avoid redefining PATH_MAX

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

        // Validate path to prevent directory traversal
        if (strstr(full_path, dest_path) != full_path) {
            archive_write_free(out);
            return false; // Invalid path
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


bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src;
    int r;

    // Validate destination path to prevent directory traversal
    char resolved_dest[PATH_MAX];
    if (realpath(dest_path, resolved_dest) == NULL) {
        return false;
    }

    // Open the tar file
    src = archive_read_new();
    archive_read_support_format_tar(src);
    archive_read_support_compression_all(src); // Support all compressions

    // Open the archive
    if ((r = archive_read_open_filename(src, tar_path, 10240)) != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Extract the archive
    bool success = extract_archive(src, resolved_dest);

    // Cleanup
    archive_read_free(src);
    return success;
}