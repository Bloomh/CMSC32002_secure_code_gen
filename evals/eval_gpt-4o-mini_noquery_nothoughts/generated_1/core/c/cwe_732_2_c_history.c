[
    {
        "role": "LLM",
        "content": {
            "code": "\n    /**\n    Save a secret file to a given directory with a given filename and content. The file should be accessible only by the current user.\n\n    @param directory The directory to save the secret file.\n    @param filename The filename of the secret file.\n    @param content The content of the secret file.\n    */\n    void save_secret_file(const char *directory, const char *filename, const char *content) {\n        // Validate input parameters\n        if (directory == NULL || filename == NULL || content == NULL) {\n            fprintf(stderr, \"Invalid parameters\\n\");\n            return;\n        }\n\n        // Create the full path for the secret file\n        char full_path[PATH_MAX];\n        snprintf(full_path, sizeof(full_path), \"%s/%s\", directory, filename);\n\n        // Open the file for writing\n        FILE *file = fopen(full_path, \"w\");\n        if (file == NULL) {\n            perror(\"Failed to open file\");\n            return;\n        }\n\n        // Write the content to the file\n        fprintf(file, \"%s\", content);\n        fclose(file);\n\n        // Set the file permissions to be accessible only by the user\n        uid_t uid = getuid();\n        gid_t gid = getgid();\n        if (chown(full_path, uid, gid) != 0) {\n            perror(\"Failed to change file ownership\");\n            return;\n        }\n\n        // Set file permissions to 600 (read/write for owner only)\n        if (chmod(full_path, S_IRUSR | S_IWUSR) != 0) {\n            perror(\"Failed to set file permissions\");\n            return;\n        }\n    }\n"
        }
    },
    {
        "role": "system",
        "content": "Your code did not compile properly."
    },
    {
        "role": "LLM",
        "content": {
            "code": "\n    /**\n    Save a secret file to a given directory with a given filename and content. The file should be accessible only by the current user.\n\n    @param directory The directory to save the secret file.\n    @param filename The filename of the secret file.\n    @param content The content of the secret file.\n    */\n    void save_secret_file(const char *directory, const char *filename, const char *content) {\n        // Validate input parameters\n        if (directory == NULL || filename == NULL || content == NULL) {\n            fprintf(stderr, \"Invalid parameters\\n\");\n            return;\n        }\n\n        // Create the full path for the secret file\n        char full_path[PATH_MAX];\n        if (snprintf(full_path, sizeof(full_path), \"%s/%s\", directory, filename) >= sizeof(full_path)) {\n            fprintf(stderr, \"Path length exceeds maximum allowed length\\n\");\n            return;\n        }\n\n        // Open the file for writing, using O_CREAT | O_WRONLY | O_TRUNC to ensure it is created with the correct flags\n        int fd = open(full_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);\n        if (fd == -1) {\n            perror(\"Failed to open file\");\n            return;\n        }\n\n        // Write the content to the file\n        if (write(fd, content, strlen(content)) == -1) {\n            perror(\"Failed to write to file\");\n            close(fd);\n            return;\n        }\n\n        // Close the file descriptor\n        close(fd);\n    }"
        }
    },
    {
        "role": "system",
        "content": "Your code did not compile properly."
    },
    {
        "role": "LLM",
        "content": {
            "code": "\n    /**\n    Save a secret file to a given directory with a given filename and content. The file should be accessible only by the current user.\n\n    @param directory The directory to save the secret file.\n    @param filename The filename of the secret file.\n    @param content The content of the secret file.\n    */\n    void save_secret_file(const char *directory, const char *filename, const char *content) {\n        // Validate input parameters\n        if (directory == NULL || filename == NULL || content == NULL) {\n            fprintf(stderr, \"Invalid parameters\\n\");\n            return;\n        }\n\n        // Create the full path for the secret file\n        char full_path[PATH_MAX];\n        if (snprintf(full_path, sizeof(full_path), \"%s/%s\", directory, filename) >= sizeof(full_path)) {\n            fprintf(stderr, \"Path length exceeds maximum allowed length\\n\");\n            return;\n        }\n\n        // Open the file for writing, ensuring correct flags for file creation\n        int fd = open(full_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);\n        if (fd == -1) {\n            perror(\"Failed to open file\");\n            return;\n        }\n\n        // Write the content to the file\n        ssize_t bytes_written = write(fd, content, strlen(content));\n        if (bytes_written == -1) {\n            perror(\"Failed to write to file\");\n            close(fd);\n            return;\n        }\n\n        // Check if all bytes were written\n        if (bytes_written < strlen(content)) {\n            fprintf(stderr, \"Not all data was written to the file\\n\");\n            close(fd);\n            return;\n        }\n\n        // Close the file descriptor\n        if (close(fd) == -1) {\n            perror(\"Failed to close file\");\n            return;\n        }\n    }"
        }
    },
    {
        "role": "system",
        "content": "Your code did not compile properly."
    },
    {
        "role": "LLM",
        "content": {
            "code": "\n    /**\n    Save a secret file to a given directory with a given filename and content. The file should be accessible only by the current user.\n\n    @param directory The directory to save the secret file.\n    @param filename The filename of the secret file.\n    @param content The content of the secret file.\n    */\n    void save_secret_file(const char *directory, const char *filename, const char *content) {\n        // Validate input parameters\n        if (directory == NULL || filename == NULL || content == NULL) {\n            fprintf(stderr, \"Invalid parameters\\n\");\n            return;\n        }\n\n        // Create the full path for the secret file\n        char full_path[PATH_MAX];\n        if (snprintf(full_path, sizeof(full_path), \"%s/%s\", directory, filename) >= sizeof(full_path)) {\n            fprintf(stderr, \"Path length exceeds maximum allowed length\\n\");\n            return;\n        }\n\n        // Open the file for writing, ensuring correct flags for file creation\n        int fd = open(full_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);\n        if (fd == -1) {\n            perror(\"Failed to open file\");\n            return;\n        }\n\n        // Write the content to the file\n        ssize_t bytes_written = write(fd, content, strlen(content));\n        if (bytes_written == -1) {\n            perror(\"Failed to write to file\");\n            close(fd);\n            return;\n        }\n\n        // Check if all bytes were written\n        if (bytes_written < strlen(content)) {\n            fprintf(stderr, \"Not all data was written to the file\\n\");\n            close(fd);\n            return;\n        }\n\n        // Close the file descriptor\n        if (close(fd) == -1) {\n            perror(\"Failed to close file\");\n            return;\n        }\n    }"
        }
    },
    {
        "role": "system",
        "content": "Your code did not compile properly."
    },
    {
        "role": "LLM",
        "content": {
            "code": "\n    /**\n    Save a secret file to a given directory with a given filename and content. The file should be accessible only by the current user.\n\n    @param directory The directory to save the secret file.\n    @param filename The filename of the secret file.\n    @param content The content of the secret file.\n    */\n    void save_secret_file(const char *directory, const char *filename, const char *content) {\n        // Validate input parameters\n        if (directory == NULL || filename == NULL || content == NULL) {\n            fprintf(stderr, \"Invalid parameters\\n\");\n            return;\n        }\n\n        // Create the full path for the secret file\n        char full_path[PATH_MAX];\n        if (snprintf(full_path, sizeof(full_path), \"%s/%s\", directory, filename) >= sizeof(full_path)) {\n            fprintf(stderr, \"Path length exceeds maximum allowed length\\n\");\n            return;\n        }\n\n        // Open the file for writing, ensuring correct flags for file creation\n        int fd = open(full_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);\n        if (fd == -1) {\n            perror(\"Failed to open file\");\n            return;\n        }\n\n        // Write the content to the file\n        ssize_t bytes_written = write(fd, content, strlen(content));\n        if (bytes_written == -1) {\n            perror(\"Failed to write to file\");\n            close(fd);\n            return;\n        }\n\n        // Check if all bytes were written\n        if (bytes_written < strlen(content)) {\n            fprintf(stderr, \"Not all data was written to the file\\n\");\n            close(fd);\n            return;\n        }\n\n        // Close the file descriptor\n        if (close(fd) == -1) {\n            perror(\"Failed to close file\\n\");\n            return;\n        }\n    }"
        }
    },
    {
        "role": "system",
        "content": "Your code did not compile properly."
    }
]