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
    // Validate input parameters
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "Invalid input parameters.\n");
        return;
    }

    // Construct full path
    size_t path_length = strlen(directory) + strlen(filename) + 2; // +2 for '/' and null terminator
    char *full_path = malloc(path_length);
    if (full_path == NULL) {
        perror("Failed to allocate memory");
        return;
    }
    snprintf(full_path, path_length, "%s/%s", directory, filename);

    // Check if the directory exists and is indeed a directory
    struct stat dir_stat;
    if (stat(directory, &dir_stat) != 0 || !S_ISDIR(dir_stat.st_mode)) {
        fprintf(stderr, "Directory does not exist or is not a directory.\n");
        free(full_path);
        return;
    }

    // Open file for writing
    FILE *file = fopen(full_path, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        free(full_path);
        return;
    }

    // Write content to file
    if (fputs(content, file) == EOF) {
        perror("Failed to write content to file");
        fclose(file);
        free(full_path);
        return;
    }

    // Close the file
    fclose(file);

    // Set file permissions to be accessible only by the owner
    if (chmod(full_path, S_IRUSR | S_IWUSR) != 0) {
        perror("Failed to set file permissions");
    }

    // Clean up
    free(full_path);
}
```