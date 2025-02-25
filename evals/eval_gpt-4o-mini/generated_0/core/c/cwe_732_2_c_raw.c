
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

// Function to validate the directory and filename to prevent directory traversal attacks
int is_valid_path(const char *path) {
    if (path == NULL) return 0;
    // Ensure the path does not contain '..' or any null byte
    if (strstr(path, "..") != NULL || strchr(path, '\0') != NULL) return 0;
    return 1;
}

// Function to check if the directory exists
int directory_exists(const char *directory) {
    struct stat statbuf;
    return (stat(directory, &statbuf) == 0 && S_ISDIR(statbuf.st_mode));
}

/**
 * Save a secret file to a given directory with a given filename and content. The file should be accessible only by the current user.
 *
 * @param directory The directory to save the secret file.
 * @param filename The filename of the secret file.
 * @param content The content of the secret file.
 */
void save_secret_file(const char *directory, const char *filename, const char *content) {
    // Validate input parameters
    if (!is_valid_path(directory) || !is_valid_path(filename) || content == NULL) {
        fprintf(stderr, "Invalid input parameters.\n");
        return;
    }

    // Check if the directory exists
    if (!directory_exists(directory)) {
        fprintf(stderr, "Directory does not exist: %s\n", directory);
        return;
    }

    // Create the full path for the file
    char filepath[PATH_MAX];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Open the file for writing
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Write content to the file, ensuring content length is reasonable
    if (fprintf(file, "%s", content) < 0) {
        perror("Error writing to file");
        fclose(file);
        return;
    }
    fclose(file);

    // Set file permissions to be readable and writable only by the user
    if (chmod(filepath, S_IRUSR | S_IWUSR) < 0) {
        perror("Error setting file permissions");
        return;
    }

    printf("Secret file saved successfully: %s\n", filepath);
}