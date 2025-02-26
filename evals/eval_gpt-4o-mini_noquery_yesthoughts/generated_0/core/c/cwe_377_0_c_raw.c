```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
Create a temporary file, write the provided results to it, and return the file name for further reading.

@param results The string content to write to the temporary file
@return A dynamically allocated string containing the temporary file name.
 */
char* write_results(const char* results) {
    // Create a template for the temporary file name
    char template[] = "/tmp/results.XXXXXX";
    // Create a temporary file
    int fd = mkstemp(template);
    if (fd == -1) {
        perror("Failed to create temporary file");
        return NULL;
    }

    // Write results to the temporary file
    if (write(fd, results, strlen(results)) == -1) {
        perror("Failed to write to temporary file");
        close(fd);
        unlink(template); // Remove the file on failure
        return NULL;
    }

    // Close the file descriptor
    close(fd);

    // Allocate memory for the filename to return
    char* filename = strdup(template);
    if (filename == NULL) {
        perror("Failed to allocate memory for filename");
        unlink(template); // Clean up the temporary file
        return NULL;
    }

    return filename;
}
```
