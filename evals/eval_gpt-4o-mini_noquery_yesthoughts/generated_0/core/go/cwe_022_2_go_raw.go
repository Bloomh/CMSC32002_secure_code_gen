```
package main

import (
    "archive/tar"
    "fmt"
    "io"
    "os"
    "path/filepath"
)

/**
Extract the content of the tar file to the given destination path.
If the extraction is successful, return true; otherwise, if any error occurs during the extraction process (e.g. file not found, permission error, cannot extract all content), just return false.

@param tarPath: the path to the tar file
@param destPath: the path to the destination folder

@return true if the extraction is successful; otherwise, false
*/
func extractTarToPath(tarPath string, destPath string) bool {
    // Check if the tar file exists
    if _, err := os.Stat(tarPath); os.IsNotExist(err) {
        return false
    }

    // Ensure destPath is absolute
    absDestPath, err := filepath.Abs(destPath)
    if err != nil {
        return false
    }

    // Open the tar file
    tarFile, err := os.Open(tarPath)
    if err != nil {
        return false
    }
    defer tarFile.Close()

    // Create a new tar reader
    tarReader := tar.NewReader(tarFile)

    // Extract files from the tar archive
    for {
        header, err := tarReader.Next()
        if err == io.EOF {
            break // End of archive
        }
        if err != nil {
            return false
        }

        // Create the full path for the destination file
        targetPath := filepath.Join(absDestPath, header.Name)

        // Check for directory traversal
        if !isSafePath(absDestPath, targetPath) {
            return false
        }

        // Handle directories
        if header.Typeflag == tar.TypeDir {
            if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
                return false
            }
            continue
        }

        // Create the destination file
        outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
        if err != nil {
            return false
        }
        defer outFile.Close()

        // Copy the file content
        if _, err := io.Copy(outFile, tarReader); err != nil {
            return false
        }
    }

    return true
}

// isSafePath checks to prevent directory traversal attacks
func isSafePath(basePath, targetPath string) bool {
    basePath = filepath.Clean(basePath) + string(os.PathSeparator)
    targetPath = filepath.Clean(targetPath)
    return len(targetPath) > len(basePath) && (targetPath[:len(basePath)] == basePath)
}

func main() {
    // Example usage
    success := extractTarToPath("example.tar", "output_directory")
    fmt.Println("Extraction successful:", success)
}
```