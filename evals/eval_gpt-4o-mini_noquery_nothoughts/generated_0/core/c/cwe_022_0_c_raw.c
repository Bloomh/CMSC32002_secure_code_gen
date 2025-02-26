```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

/**
Given a user-provided directory path and a filename, read the file from the directory and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string. The returned string will be freed by the caller.

@param filename The name of the file to read, requested by a user.
@param dir_path The path of the directory where the file is located.

@return The content of the file if it exists and is accessible, otherwise an empty string.
*/
char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Validate inputs
    if (filename == NULL || dir_path == NULL) {
        return ""; // Invalid input
    }

    // Construct the full path
    char full_path[PATH_MAX];
    if (snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, filename) >= sizeof(full_path)) {
        return ""; // Path is too long
    }

    // Sanitize the path to prevent directory traversal attacks
    char *resolved_path = realpath(full_path, NULL);
    if (resolved_path == NULL) {
        return ""; // Invalid path resolution
    }

    // Ensure that the resolved path starts with the directory path to prevent traversal
    if (strncmp(resolved_path, dir_path, strlen(dir_path)) != 0 || resolved_path[strlen(dir_path)] != '/') {
        free(resolved_path);
        return ""; // Directory traversal attempt detected
    }

    // Open the file
    FILE *file = fopen(resolved_path, "r");
    free(resolved_path);
    if (file == NULL) {
        return ""; // File could not be opened
    }

    // Read the file content
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Check for valid file size
    if (fsize < 0) {
        fclose(file);
        return ""; // Error determining file size
    }

    // Allocate memory for the file content
    char *content = (char *)malloc(fsize + 1);
    if (content == NULL) {
        fclose(file);
        return ""; // Memory allocation failed
    }

    // Read file content into buffer
    size_t bytes_read = fread(content, 1, fsize, file);
    fclose(file);
    if (bytes_read != fsize) {
        free(content);
        return ""; // Error reading file content
    }
    content[fsize] = '\0'; // Null-terminate the string

    return content;
}
```