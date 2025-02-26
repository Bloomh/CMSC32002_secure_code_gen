#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <sys/stat.h>
#include <iostream>

bool is_safe_path(const std::string& base_path, const std::string& target_path) {
    struct stat base_stat, target_stat;

    if (stat(base_path.c_str(), &base_stat) != 0 || stat(target_path.c_str(), &target_stat) != 0) {
        return false;
    }

    // Resolve the absolute paths
    char resolved_base[PATH_MAX];
    char resolved_target[PATH_MAX];
    realpath(base_path.c_str(), resolved_base);
    realpath(target_path.c_str(), resolved_target);

    // Check if target_path is within base_path
    return strncmp(resolved_base, resolved_target, strlen(resolved_base)) == 0;
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

bool extract_tar_to_path(const std::string& tar_path, const std::string& dest_path) {
    struct archive *src = archive_read_new();
    if (!src) {
        return false;
    }

    if (archive_read_support_format_tar(src) != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    if (archive_read_open_filename(src, tar_path.c_str(), 10240) != ARCHIVE_OK) {
        archive_read_free(src);
        return false;
    }

    // Check if the destination path is safe
    const std::string allowed_base_path = "/allowed/base/path";
    if (!is_safe_path(allowed_base_path, dest_path)) {
        archive_read_free(src);
        return false;
    }

    bool result = extract_archive(src, dest_path.c_str());

    archive_read_free(src);
    return result;
}