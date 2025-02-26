```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

/**
 * Given a user-provided directory path and a filename, read the file from the directory and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string. The returned string will be freed by the caller.
 *
 * @param filename The name of the file to read, requested by a user.
 * @param dir_path The path of the directory where the file is located.
 *
 * @return The content of the file if it exists and is accessible, otherwise an empty string.
 */
char *read_file_from_dir(const char *filename, const char *dir_path) {
    // Validate input parameters
    if (filename == NULL || dir_path == NULL || strlen(filename) == 0 || strlen(dir_path) == 0) {
        return ""; // Return empty string for invalid input
    }

    // Validate filename to prevent directory traversal
    if (strstr(filename, "../") || strstr(filename, "/") || strstr(filename, "\\")) {
        return ""; // Invalid filename
    }

    // Create a buffer to hold the full file path
    char full_path[PATH_MAX];

    // Construct the full path safely
    if (snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, filename) >= sizeof(full_path)) {
        return ""; // Return empty string if path is too long
    }

    // Open the file
    FILE *file = fopen(full_path, "r");
    if (file == NULL) {
        return ""; // Return empty string on error
    }

    // Read the content of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Check for valid file size
    if (file_size < 0) {
        fclose(file);
        return ""; // Return empty string if file size is invalid
    }

    // Allocate memory for the content
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return ""; // Return empty string on memory allocation failure
    }

    // Read the file into the buffer
    size_t read_size = fread(content, 1, file_size, file);
    fclose(file);

    // Null-terminate the string
    content[read_size] = '\0';

    return content;
}
```