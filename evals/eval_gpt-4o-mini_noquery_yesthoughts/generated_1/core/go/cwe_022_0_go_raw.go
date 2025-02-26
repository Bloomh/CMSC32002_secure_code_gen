```
import (
    "io/ioutil"
    "log"
    "os"
    "path/filepath"
)

/**
Given a user-provided directory path and a filename, read the file from the directory and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string. The returned string will be freed by the caller.

@param filename The name of the file to read, requested by a user.
@param dir_path The path of the directory where the file is located.

@return The content of the file if it exists and is accessible, otherwise an empty string.
*/
func readFileFromDir(filename, dirPath string) string {
    // Clean and validate the directory path
    cleanDirPath := filepath.Clean(dirPath)
    // Join the directory path with the filename
    filePath := filepath.Join(cleanDirPath, filename)

    // Prevent directory traversal attacks
    if !filepath.HasPrefix(filePath, cleanDirPath) {
        return ""
    }

    // Read the file content
    content, err := ioutil.ReadFile(filePath)
    if err != nil {
        log.Println("Error reading file:", err)
        return ""
    }

    return string(content)
}
```