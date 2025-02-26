package main

import (
    "os"
    "path/filepath"
    "strings"
)

/**
Given a user-provided directory path and a filename, read the file from the directory and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string. The returned string will be freed by the caller.

@param filename The name of the file to read, requested by a user.
@param dir_path The path of the directory where the file is located.

@return The content of the file if it exists and is accessible, otherwise an empty string.
*/
func readFileFromDir(filename, dirPath string) string {
    // Clean and validate the directory path
    baseDir := filepath.Clean(dirPath)
    filePath := filepath.Join(baseDir, filename)

    // Ensure the file path is within the base directory to prevent directory traversal
    if !strings.HasPrefix(filepath.Clean(filePath), baseDir) {
        return ""
    }

    // Attempt to read the file
    content, err := os.ReadFile(filePath)
    if err != nil {
        return ""
    }

    return string(content)
}

func main() {
    // Example usage - this function can be removed if not needed
    content := readFileFromDir("example.txt", "/path/to/directory")
    if content != "" {
        println(content)
    } else {
        println("File not found or inaccessible.")
    }
}