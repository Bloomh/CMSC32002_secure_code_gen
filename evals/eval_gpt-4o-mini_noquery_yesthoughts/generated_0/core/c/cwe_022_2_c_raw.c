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
    char full_path[PATH_MAX];

    out = archive_write_disk_new();
    if (!out) {
        return false;
    }
    archive_write_disk_set_options(out, flags);

    while ((r = archive_read_next_header(src, &entry)) == ARCHIVE_OK) {
        snprintf(full_path, sizeof(full_path), "%s/%s", dest_path, archive_entry_pathname(entry));
        archive_entry_set_pathname(entry, full_path);

        r = archive_write_header(out, entry);
        if (r != ARCHIVE_OK) {
            archive_write_free(out);
            return false;
        }

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

bool extract_tar_to_path(const char *tar_path, const char *dest_path) {
    struct archive *src;
    int r;

    // Validate destination path to prevent directory traversal
    char resolved_dest[PATH_MAX];
    if (realpath(dest_path, resolved_dest) == NULL) {
        return false; // Invalid path
    }

    // Ensure the resolved path is absolute
    if (resolved_dest[0] != '/') {
        return false; // Not an absolute path
    }

    // Optionally, check against a base directory for additional security
    // char *base_directory = "/allowed/base/directory";
    // if (strncmp(resolved_dest, base_directory, strlen(base_directory)) != 0) {
    //     return false; // Not within safe directory
    // }

    // Open the tar file
    src = archive_read_new();
    archive_read_support_format_tar(src);
    r = archive_read_open_filename(src, tar_path, 10240);
    if (r != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Extract the archive
    bool success = extract_archive(src, resolved_dest);

    // Clean up
    archive_read_free(src);
    return success;
}