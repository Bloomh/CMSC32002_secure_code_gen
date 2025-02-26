#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <archive.h>
#include <archive_entry.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

#define PATH_MAX 512

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

bool is_safe_path(const char *base, const char *path) {
    char resolved_base[PATH_MAX];
    char resolved_path[PATH_MAX];

    // Resolve the base and path to their absolute forms
    if (realpath(base, resolved_base) == NULL || realpath(path, resolved_path) == NULL) {
        return false;
    }

    // Check if the resolved path starts with the resolved base path
    return strncmp(resolved_base, resolved_path, strlen(resolved_base)) == 0;
}

bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src;
    int r;

    // Check if the tar file exists
    struct stat st;
    if (stat(tar_path, &st) != 0) {
        fprintf(stderr, "Error: Tar file does not exist or cannot be accessed.\n");
        return false;
    }

    // Validate input paths
    if (!is_safe_path(dest_path, tar_path)) {
        fprintf(stderr, "Unsafe path detected!\n");
        return false;
    }

    // Open the tar file
    src = archive_read_new();
    archive_read_support_format_tar(src);
    archive_read_support_compression_all(src);

    if ((r = archive_read_open_filename(src, tar_path, 10240))) {
        fprintf(stderr, "Could not open %s: %s\n", tar_path, archive_error_string(src));
        archive_read_free(src);
        return false;
    }

    // Extract the archive
    bool success = extract_archive(src, dest_path);

    // Clean up
    archive_read_free(src);
    return success;
}