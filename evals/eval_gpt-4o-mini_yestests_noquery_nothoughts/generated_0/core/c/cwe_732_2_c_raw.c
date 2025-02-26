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
    // Check for null pointers
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "Invalid input: directory, filename, or content is NULL.\n");
        return;
    }

    // Construct the full path for the file
    char full_path[512];
    if (snprintf(full_path, sizeof(full_path), "%s/%s", directory, filename) >= sizeof(full_path)) {
        fprintf(stderr, "Path length exceeds buffer size.\n");
        return;
    }

    // Open the file for writing
    FILE *file = fopen(full_path, "w");
    if (file == NULL) {
        perror("Unable to open file for writing");
        return;
    }

    // Write content to the file
    if (fprintf(file, "%s", content) < 0) {
        perror("Error writing to file");
        fclose(file);
        return;
    }
    fclose(file);

    // Set file permissions to allow only the owner to read and write
    if (chmod(full_path, S_IRUSR | S_IWUSR) < 0) {
        perror("Unable to set file permissions");
    }
}
```