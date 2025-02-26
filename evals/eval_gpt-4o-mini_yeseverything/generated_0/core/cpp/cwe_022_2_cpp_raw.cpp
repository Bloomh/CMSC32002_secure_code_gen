#include <archive.h>
#include <archive_entry.h>
#include <string>
#include <sys/stat.h>
#include <iostream>
#include <filesystem>

using namespace std;

bool is_safe_path(const string &base, const string &path) {
    namespace fs = std::filesystem;
    fs::path basePath(fs::absolute(base));
    fs::path fullPath = fs::absolute(basePath / path);
    return fullPath.string().find(basePath.string()) == 0;
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
        const char *entry_path = archive_entry_pathname(entry);

        // Validate the path to prevent directory traversal
        if (!is_safe_path(dest_path, entry_path)) {
            archive_write_free(out);
            return false;
        }

        // Create full path
        snprintf(full_path, sizeof(full_path), "%s/%s",
                dest_path, entry_path);
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
    struct archive *archive = archive_read_new();
    if (!archive) {
        return false;
    }

    if (archive_read_support_format_tar(archive) != ARCHIVE_OK) {
        archive_read_free(archive);
        return false;
    }

    if (archive_read_open_filename(archive, tar_path.c_str(), 10240) != ARCHIVE_OK) {
        archive_read_free(archive);
        return false;
    }

    bool result = extract_archive(archive, dest_path.c_str());
    archive_read_free(archive);
    return result;
}