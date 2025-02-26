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
void save_secret_file(const char *directory, const char *filename, const char *content) {
    // Construct the full path for the file
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // Create and open the file for writing
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    // Write content to the file
    if (fwrite(content, sizeof(char), strlen(content), file) < strlen(content)) {
        perror("Failed to write content to file");
        fclose(file);
        return;
    }

    // Close the file
    if (fclose(file) != 0) {
        perror("Failed to close file");
        return;
    }

    // Set the file permissions to be accessible only by the owner
    if (chmod(filepath, S_IRUSR | S_IWUSR) != 0) {
        perror("Failed to set file permissions");
        return;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <directory> <filename> <content>\n", argv[0]);
        return EXIT_FAILURE;
    }

    save_secret_file(argv[1], argv[2], argv[3]);
    return EXIT_SUCCESS;
}