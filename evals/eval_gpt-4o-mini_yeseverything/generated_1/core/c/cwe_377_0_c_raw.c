#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

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

    // Create a unique temporary file name
    char template[] = "/tmp/tempfileXXXXXX";
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }

    // Open the temporary file for writing
    FILE* temp_file = fdopen(fd, "w");
    if (temp_file == NULL) {
        close(fd);
        return NULL;
    }

    // Write results to the file
    if (fprintf(temp_file, "%s", results) < 0) {
        fclose(temp_file);
        return NULL;
    }

    // Close the file
    if (fclose(temp_file) != 0) {
        return NULL;
    }

    // Return the name of the temporary file
    // Allocate memory for the filename to be returned
    char* temp_filename = strdup(template);
    if (temp_filename == NULL) {
        return NULL;
    }

    return temp_filename;
}