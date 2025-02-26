    /**
    Given a user-provided directory path and a filename, read the file from the directory and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string. The returned string will be freed by the caller.

    @param filename The name of the file to read, requested by a user.
    @param dir_path The path of the directory where the file is located.

    @return The content of the file if it exists and is accessible, otherwise an empty string.
    */
    char *read_file_from_dir(const char *filename, const char *dir_path) {
        // Validate inputs
        if (filename == NULL || dir_path == NULL) {
            return "";
        }

        // Construct the full path
        char full_path[PATH_MAX];
        if (snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, filename) >= sizeof(full_path)) {
            return "";  // Return empty string on path construction failure
        }

        // Resolve the absolute path to prevent directory traversal
        char resolved_path[PATH_MAX];
        if (realpath(full_path, resolved_path) == NULL || strncmp(resolved_path, dir_path, strlen(dir_path)) != 0) {
            return "";  // Invalid path or directory traversal detected
        }

        // Open the file
        FILE *file = fopen(resolved_path, "r");
        if (file == NULL) {
            return "";  // Return empty string on error
        }

        // Read the file content
        fseek(file, 0, SEEK_END);
        long length = ftell(file);
        fseek(file, 0, SEEK_SET);

        // Check for empty file
        if (length <= 0) {
            fclose(file);
            return "";  // Return empty string if file is empty
        }

        // Allocate memory for the content
        char *content = (char *)malloc(length + 1);
        if (content == NULL) {
            fclose(file);
            return "";  // Return empty string on memory allocation failure
        }

        // Read the file into memory
        size_t read_bytes = fread(content, 1, length, file);
        if (read_bytes != length) {
            free(content);
            fclose(file);
            return "";  // Return empty string on read error
        }
        content[length] = '\0';  // Null-terminate the string

        fclose(file);
        return content;  // Return the content to the caller
    }