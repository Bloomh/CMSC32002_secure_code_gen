#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

/**
 * Given a user-provided directory path and a filename, read the file from the directory and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string. The returned string will be freed by the caller.
 *
 * @param filename The name of the file to read, requested by a user.
 * @param dir_path The path of the directory where the file is located.
 *
 * @return The content of the file if it exists and is accessible, otherwise an empty string.
 */
char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Validate inputs
    if (filename == NULL || dir_path == NULL) {
        return "";  // Null inputs are invalid
    }

    // Check for invalid characters in filename
    for (const char *p = filename; *p; p++) {
        if (*p == '/' || *p == '\' || *p == '..') {
            return "";  // Invalid filename
        }
    }

    // Create a buffer for the full file path
    char filepath[PATH_MAX];

    // Safely construct the file path
    if (snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, filename) >= sizeof(filepath)) {
        return "";  // Buffer overflow risk
    }

    // Resolve the full path and check for directory traversal
    char *resolved_path = realpath(filepath, NULL);
    if (resolved_path == NULL || strncmp(resolved_path, dir_path, strlen(dir_path)) != 0) {
        free(resolved_path);
        return "";  // Directory traversal attempt detected
    }

    // Open the file
    FILE *file = fopen(resolved_path, "r");
    free(resolved_path);
    if (file == NULL) {
        return "";  // File not found or permission denied
    }

    // Read file content
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Check for negative file size
    if (filesize < 0) {
        fclose(file);
        return "";  // Error occurred while determining file size
    }

    // Allocate memory for the file content
    char *content = (char *)malloc(filesize + 1);
    if (content == NULL) {
        fclose(file);
        return "";  // Memory allocation failed
    }

    // Read the file into the buffer
    size_t bytes_read = fread(content, 1, filesize, file);
    content[bytes_read] = '\0';  // Null-terminate the string

    // Clean up
    fclose(file);
    return content;
}