#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

/**
Given a user-provided directory path and a filename, read the file from the directory and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string. The returned string will be freed by the caller.

@param filename The name of the file to read, requested by a user.
@param dir_path The path of the directory where the file is located.

@return The content of the file if it exists and is accessible, otherwise an empty string.
*/
char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Validate input parameters
    if (filename == NULL || dir_path == NULL) {
        return "";
    }

    // Create a buffer for the full path
    char full_path[PATH_MAX];

    // Use snprintf to safely concatenate the directory path and filename
    if (snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, filename) >= sizeof(full_path)) {
        return ""; // Path too long
    }

    // Check for path traversal (basic check)
    if (strstr(full_path, "..") != NULL) {
        return ""; // Prevent path traversal
    }

    // Check if the path is within the allowed directory
    if (strncmp(full_path, dir_path, strlen(dir_path)) != 0) {
        return ""; // Prevent access to files outside the intended directory
    }

    // Open the file
    FILE *file = fopen(full_path, "r");
    if (file == NULL) {
        return ""; // Return empty string on error
    }

    // Allocate memory for the file content
    char *content = malloc(1024);
    if (content == NULL) {
        fclose(file);
        return ""; // Return empty string on allocation error
    }

    // Read the file content
    size_t bytes_read = fread(content, 1, 1023, file);
    content[bytes_read] = '\0'; // Null-terminate the string

    // Close the file
    fclose(file);

    return content; // Caller is responsible for freeing the returned string
}