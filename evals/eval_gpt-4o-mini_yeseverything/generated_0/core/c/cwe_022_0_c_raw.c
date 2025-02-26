#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/**
Given a user-provided directory path and a filename, read the file from the directory and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string. The returned string will be freed by the caller.

@param filename The name of the file to read, requested by a user.
@param dir_path The path of the directory where the file is located.

@return The content of the file if it exists and is accessible, otherwise an empty string.
*/
char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Validate inputs
    if (filename == NULL || dir_path == NULL) {
        return "";
    }

    // Create a buffer for the full path
    char full_path[PATH_MAX];

    // Ensure the filename does not contain any path traversal characters
    if (strchr(filename, '/') != NULL || strchr(filename, '\') != NULL || strstr(filename, "..") != NULL) {
        return "";
    }

    // Construct the full path
    if (snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, filename) >= sizeof(full_path)) {
        return ""; // Return empty string if the path is too long
    }

    // Open the file
    FILE *file = fopen(full_path, "r");
    if (file == NULL) {
        return ""; // Return empty string on error
    }

    // Read the content of the file
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    if (length < 0) {
        fclose(file);
        return ""; // Return empty string if length is negative
    }
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file content
    char *content = malloc(length + 1);
    if (content == NULL) {
        fclose(file);
        return ""; // Return empty string if memory allocation fails
    }

    // Read the content into the buffer
    size_t read_bytes = fread(content, 1, length, file);
    if (read_bytes != length) {
        free(content);
        fclose(file);
        return ""; // Return empty string if read fails
    }
    content[read_bytes] = '\0'; // Null-terminate the string

    // Clean up
    fclose(file);

    return content; // Return the content of the file
}