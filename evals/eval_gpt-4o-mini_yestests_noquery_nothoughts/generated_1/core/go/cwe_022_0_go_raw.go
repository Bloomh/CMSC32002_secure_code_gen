```
/**
Given a user-provided directory path and a filename, read the file from the directory and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string. The returned string will be freed by the caller.

@param filename The name of the file to read, requested by a user.
@param dir_path The path of the directory where the file is located.

@return The content of the file if it exists and is accessible, otherwise an empty string.
*/
func readFileFromDir(filename, dirPath string) string {
    // Sanitize the input to prevent path traversal attacks
    safeFilename := filepath.Base(filename)
    safeDirPath := filepath.Clean(dirPath)
    fullPath := filepath.Join(safeDirPath, safeFilename)

    // Read the file
    content, err := os.ReadFile(fullPath)
    if err != nil {
        // Log the error if necessary (omitted for brevity)
        return ""
    }

    return string(content)
}
```