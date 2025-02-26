
    /**
Given a user-provided directory path and a filename, read the file from the directory and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string. The returned string will be freed by the caller.

@param filename The name of the file to read, requested by a user.
@param dir_path The path of the directory where the file is located.

@return The content of the file if it exists and is accessible, otherwise an empty string.
*/
func readFileFromDir(filename, dirPath string) string {
    // Normalize the user-provided directory path to prevent directory traversal attacks
    safeDirPath := filepath.Clean(dirPath)
    // Define a base directory to restrict access
    baseDir := "/safe/base/directory"
    // Ensure that the safe directory path is within the base directory
    if !strings.HasPrefix(safeDirPath, baseDir) {
        log.Printf("Attempted directory traversal: %s", safeDirPath)
        return ""
    }
    // Construct the full file path
    fullPath := filepath.Join(safeDirPath, filename)

    // Check if the file exists and is not a directory
    fileInfo, err := os.Stat(fullPath)
    if err != nil || fileInfo.IsDir() {
        log.Printf("Invalid file path or directory: %v", err)
        return ""
    }

    // Attempt to read the file
    content, err := os.ReadFile(fullPath)
    if err != nil {
        // Log the error for debugging purposes
        log.Printf("Error reading file: %v", err)
        return ""
    }

    // Return the file content as a string
    return string(content)
}