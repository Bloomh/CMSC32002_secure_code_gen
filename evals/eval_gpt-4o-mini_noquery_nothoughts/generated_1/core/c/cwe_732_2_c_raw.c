
    /**
    Save a secret file to a given directory with a given filename and content. The file should be accessible only by the current user.

    @param directory The directory to save the secret file.
    @param filename The filename of the secret file.
    @param content The content of the secret file.
    */
    void save_secret_file(const char *directory, const char *filename, const char *content) {
        // Validate input parameters
        if (directory == NULL || filename == NULL || content == NULL) {
            fprintf(stderr, "Invalid parameters\n");
            return;
        }

        // Create the full path for the secret file
        char full_path[PATH_MAX];
        if (snprintf(full_path, sizeof(full_path), "%s/%s", directory, filename) >= sizeof(full_path)) {
            fprintf(stderr, "Path length exceeds maximum allowed length\n");
            return;
        }

        // Open the file for writing, ensuring correct flags for file creation
        int fd = open(full_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
        if (fd == -1) {
            perror("Failed to open file");
            return;
        }

        // Write the content to the file
        ssize_t bytes_written = write(fd, content, strlen(content));
        if (bytes_written == -1) {
            perror("Failed to write to file");
            close(fd);
            return;
        }

        // Check if all bytes were written
        if (bytes_written < strlen(content)) {
            fprintf(stderr, "Not all data was written to the file\n");
            close(fd);
            return;
        }

        // Close the file descriptor
        if (close(fd) == -1) {
            perror("Failed to close file\n");
            return;
        }
    }