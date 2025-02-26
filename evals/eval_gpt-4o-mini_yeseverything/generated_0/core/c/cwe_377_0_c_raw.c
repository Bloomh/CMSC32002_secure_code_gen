#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // Create a template for the temporary file name
    char template[] = "/tmp/resultsXXXXXX";
    // Create a temporary file
    int fd = mkstemp(template);
    if (fd == -1) {
        perror("Failed to create temporary file");
        return NULL;
    }
    // Write results to the temporary file
    FILE* file = fdopen(fd, "w");
    if (file == NULL) {
        perror("Failed to open temporary file stream");
        close(fd);
        return NULL;
    }
    // Write the results to the file
    if (fprintf(file, "%s", results) < 0) {
        perror("Failed to write to temporary file");
        fclose(file);
        return NULL;
    }
    // Close the file stream
    fclose(file);
    // Return the name of the temporary file
    char* filename = strdup(template);
    if (filename == NULL) {
        perror("Failed to allocate memory for filename");
        return NULL;
    }
    return filename;
}