```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>

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

    // Sanitize the filename to prevent path traversal
    if (strstr(filename, "..") != NULL || strchr(filename, '/') != NULL) {
        return ""; // Prevent path traversal
    }

    // Create a buffer for the full file path
    char full_path[PATH_MAX];
    if (snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, filename) >= sizeof(full_path)) {
        return ""; // Path too long
    }

    // Resolve the real path
    char *resolved_path = realpath(full_path, NULL);
    if (resolved_path == NULL) {
        return ""; // Invalid path
    }

    // Ensure the resolved path is within the expected directory
    if (strncmp(resolved_path, dir_path, strlen(dir_path)) != 0) {
        free(resolved_path);
        return ""; // Out of bounds
    }
    free(resolved_path);

    // Open the file
    FILE *file = fopen(full_path, "r");
    if (file == NULL) {
        return ""; // File not accessible
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Check for empty file
    if (file_size < 0) {
        fclose(file);
        return ""; // Error determining file size
    }

    // Allocate memory for the file content
    char *content = malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return ""; // Memory allocation failed
    }

    // Read the file content
    size_t read_size = fread(content, 1, file_size, file);
    fclose(file);

    // Null-terminate the string
    content[read_size] = '\0';

    return content;
}
```