```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

/**
 * Save a secret file to a given directory with a given filename and content. The file should be accessible only by the current user.
 *
 * @param directory The directory to save the secret file.
 * @param filename The filename of the secret file.
 * @param content The content of the secret file.
 */
void save_secret_file(const char *directory, const char *filename, const char *content) {
    // Validate input parameters
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "Invalid input parameters.\n");
        return;
    }

    // Ensure the directory is not too long
    if (strlen(directory) + strlen(filename) + 2 > PATH_MAX) {
        fprintf(stderr, "Path is too long.\n");
        return;
    }

    // Create the full path
    char filepath[PATH_MAX];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Check if the directory exists and is writable
    struct stat st;
    if (stat(directory, &st) != 0 || !S_ISDIR(st.st_mode) || !(st.st_mode & S_IWUSR)) {
        fprintf(stderr, "Directory does not exist or is not writable: %s\n", directory);
        return;
    }

    // Open the file for writing
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    // Write content to the file
    if (fprintf(file, "%s", content) < 0) {
        perror("Failed to write to file");
        fclose(file);
        return;
    }
    fclose(file);

    // Set file permissions to be accessible only by the user
    if (chmod(filepath, S_IRUSR | S_IWUSR) < 0) {
        perror("Failed to set file permissions");
    }
}
```