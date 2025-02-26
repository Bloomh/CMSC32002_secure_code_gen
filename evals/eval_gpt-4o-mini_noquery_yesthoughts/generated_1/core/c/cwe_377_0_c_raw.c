```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/**
Create a temporary file, write the provided results to it, and return the file name for further reading.

@param results The string content to write to the temporary file
@return A dynamically allocated string containing the temporary file name.
 */
char* write_results(const char* results) {
    if (results == NULL) {
        return NULL; // Handle null input
    }

    // Create a temporary file
    char temp_filename[] = "/tmp/resultsXXXXXX";
    int fd = mkstemp(temp_filename);
    if (fd == -1) {
        perror("Failed to create temporary file");
        return NULL;
    }

    // Write the results to the temporary file
    ssize_t write_size = write(fd, results, strlen(results));
    if (write_size == -1) {
        perror("Failed to write to temporary file");
        close(fd);
        unlink(temp_filename); // Remove file if write fails
        return NULL;
    }

    // Close the file descriptor
    close(fd);

    // Allocate memory for the filename to return
    char* result_filename = malloc(strlen(temp_filename) + 1);
    if (result_filename == NULL) {
        unlink(temp_filename); // Clean up if memory allocation fails
        return NULL;
    }
    strcpy(result_filename, temp_filename);

    return result_filename;
}
```