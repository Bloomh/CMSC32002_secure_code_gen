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

bool is_safe_path(const char *base, const char *path) {
    char resolved_base[PATH_MAX];
    char resolved_path[PATH_MAX];

    if (!realpath(base, resolved_base) || !realpath(path, resolved_path)) {
        return false;
    }

    return strncmp(resolved_base, resolved_path, strlen(resolved_base)) == 0;
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
    struct stat st;

    // Check if the tar file exists
    if (stat(tar_path, &st) != 0) {
        perror("stat");
        return false;
    }

    // Check if the destination path is a directory
    if (stat(dest_path, &st) != 0 || !S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Destination path is not a directory or does not exist.\n");
        return false;
    }

    // Check for safe extraction path
    if (!is_safe_path(dest_path, tar_path)) {
        fprintf(stderr, "Unsafe extraction path detected.\n");
        return false;
    }

    // Initialize the archive
    src = archive_read_new();
    archive_read_support_format_tar(src);
    archive_read_support_compression_all(src);

    // Open the tar file
    if ((r = archive_read_open_filename(src, tar_path, 10240)) != ARCHIVE_OK) {
        fprintf(stderr, "Could not open tar file: %s\n", archive_error_string(src));
        archive_read_free(src);
        return false;
    }

    // Extract the archive
    bool success = extract_archive(src, dest_path);

    // Cleanup
    archive_read_free(src);
    return success;
}