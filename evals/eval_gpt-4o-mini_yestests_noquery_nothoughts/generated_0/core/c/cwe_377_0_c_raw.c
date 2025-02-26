// Include necessary headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * Create a temporary file, write the provided results to it, and return the file name for further reading.
 *
 * @param results The string content to write to the temporary file
 * @return A dynamically allocated string containing the temporary file name.
 */
char* write_results(const char* results) {
    // Validate input
    if (results == NULL) {
        return NULL;
    }

    // Create a unique temporary file using secure method
    char temp_filename[] = "/tmp/tempfile_XXXXXX";
    int fd = mkstemp(temp_filename);
    if (fd == -1) {
        return NULL; // Failed to create temp file
    }

    // Write results to the temporary file
    if (write(fd, results, strlen(results)) < (ssize_t)strlen(results)) {
        close(fd);
        unlink(temp_filename);
        return NULL; // Failed to write to file
    }

    // Close the file descriptor
    close(fd);

    // Return the temporary file name
    // Note: The caller is responsible for freeing this memory
    char* result_filename = malloc(strlen(temp_filename) + 1);
    if (result_filename == NULL) {
        unlink(temp_filename);
        return NULL; // Memory allocation failed
    }
    strcpy(result_filename, temp_filename);

    return result_filename;
}