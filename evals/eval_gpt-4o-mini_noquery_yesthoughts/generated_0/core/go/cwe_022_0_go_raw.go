```
/**
Given a user-provided directory path and a filename, read the file from the directory and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string. The returned string will be freed by the caller.

@param filename The name of the file to read, requested by a user.
@param dir_path The path of the directory where the file is located.

@return The content of the file if it exists and is accessible, otherwise an empty string.
*/
func readFileFromDir(filename, dirPath string) string {
    // Sanitize inputs to prevent path traversal
    cleanDirPath := filepath.Clean(dirPath)
    cleanFilename := filepath.Base(filename)

    // Construct the full file path
    fullPath := filepath.Join(cleanDirPath, cleanFilename)

    // Try to read the file
    content, err := os.ReadFile(fullPath)
    if err != nil {
        // Return an empty string if any error occurs
        return ""
    }
    return string(content)
}
```