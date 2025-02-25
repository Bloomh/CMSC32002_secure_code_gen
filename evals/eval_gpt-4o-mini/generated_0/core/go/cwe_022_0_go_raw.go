import os
import path/filepath

/**
Given a user-provided directory path and a filename, read the file from the directory and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string. The returned string will be freed by the caller.

@param filename The name of the file to read, requested by a user.
@param dir_path The path of the directory where the file is located.

@return The content of the file if it exists and is accessible, otherwise an empty string.
*/
func readFileFromDir(filename, dirPath string) string {
    // Sanitize inputs to prevent directory traversal
    safeDirPath := filepath.Clean(dirPath)
    safeFileName := filepath.Base(filename)

    // Check if the sanitized directory path is valid
    dirInfo, err := os.Stat(safeDirPath)
    if err != nil || !dirInfo.IsDir() {
        return ""
    }

    // Construct the full file path
    fullPath := filepath.Join(safeDirPath, safeFileName)

    // Check if the file exists and is a regular file
    fileInfo, err := os.Stat(fullPath)
    if err != nil || fileInfo.IsDir() {
        return ""
    }

    // Read the file content
    content, err := os.ReadFile(fullPath)
    if err != nil {
        return ""
    }

    return string(content)
}