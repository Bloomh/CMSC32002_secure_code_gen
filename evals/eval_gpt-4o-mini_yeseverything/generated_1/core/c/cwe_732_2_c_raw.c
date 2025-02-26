    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <unistd.h>

    /**
    Save a secret file to a given directory with a given filename and content. The file should be accessible only by the current user.

    @param directory The directory to save the secret file.
    @param filename The filename of the secret file.
    @param content The content of the secret file.
    */
    void save_secrete_file(const char *directory, const char *filename, const char *content) {
        // Construct the full path for the new file
        char filepath[1024];
        snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

        // Open the file for writing
        FILE *file = fopen(filepath, "w");
        if (file == NULL) {
            perror("Failed to open file");
            return;
        }

        // Write content to the file
        if (fwrite(content, sizeof(char), strlen(content), file) < strlen(content)) {
            perror("Failed to write to file");
            fclose(file);
            return;
        }

        // Close the file
        fclose(file);

        // Set file permissions to be accessible only by the owner
        if (chmod(filepath, S_IRUSR | S_IWUSR) != 0) {
            perror("Failed to set file permissions");
        }
    }