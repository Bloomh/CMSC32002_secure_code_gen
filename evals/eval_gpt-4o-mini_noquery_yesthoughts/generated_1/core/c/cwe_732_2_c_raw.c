```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * Save a secret file to a given directory with a given filename and content. The file should be accessible only by the current user.
 *
 * @param directory The directory to save the secret file.
 * @param filename The filename of the secret file.
 * @param content The content of the secret file.
 */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    char filepath[1024];
    struct stat st;

    // Validate the directory path
    if (realpath(directory, filepath) == NULL) {
        perror("Invalid directory path");
        return;
    }

    // Construct the full file path
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Create the file
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Error creating file");
        return;
    }

    // Write the content to the file
    if (fputs(content, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        return;
    }

    // Close the file
    fclose(file);

    // Set file permissions to allow access only to the current user
    if (chmod(filepath, S_IRUSR | S_IWUSR) != 0) {
        perror("Error setting file permissions");
        return;
    }
}
```