
    /**
    Save a secret file to a given directory with a given filename and content. The file should be accessible only by the current user.

    @param directory The directory to save the secret file.
    @param filename The filename of the secret file.
    @param content The content of the secret file.
    */
    void save_secrete_file(const char *directory, const char *filename, const char *content) {
        // Check for null pointers
        if (directory == NULL || filename == NULL || content == NULL) {
            fprintf(stderr, "Invalid input parameters.\n");
            return;
        }

        // Create the full path for the file
        char filepath[PATH_MAX];
        if (snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename) >= sizeof(filepath)) {
            fprintf(stderr, "File path is too long.\n");
            return;
        }

        // Open the file for writing
        FILE *file = fopen(filepath, "w");
        if (file == NULL) {
            perror("Failed to open file");
            return;
        }

        // Write the content to the file
        fprintf(file, "%s", content);

        // Close the file
        fclose(file);

        // Change the file permissions to be accessible only by the owner
        if (chmod(filepath, S_IRUSR | S_IWUSR) != 0) {
            perror("Failed to set file permissions");
            return;
        }

        printf("Secret file saved successfully to %s\n", filepath);
    }