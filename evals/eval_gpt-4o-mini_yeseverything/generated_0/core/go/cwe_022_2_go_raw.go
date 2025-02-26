package main

import (
    "archive/tar"
    "io"
    "log"
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
    // Validate destPath to prevent directory traversal
    if !isSafePath(destPath) {
        log.Println("Unsafe destination path detected:", destPath)
        return false
    }

    // Open the tar file
    tarFile, err := os.Open(tarPath)
    if err != nil {
        log.Println("Error opening tar file:", err)
        return false
    }
    defer tarFile.Close()

    // Create a new tar reader
    tarReader := tar.NewReader(tarFile)

    // Iterate through the files in the tar archive
    for {
        header, err := tarReader.Next()
        if err == io.EOF {
            break // End of archive
        }
        if err != nil {
            log.Println("Error reading tar entry:", err)
            return false
        }

        // Construct the full path for the file to be extracted
        targetPath := filepath.Join(destPath, header.Name)

        // Validate the target path to prevent directory traversal
        if !isSafePath(targetPath) {
            log.Println("Unsafe path detected:", targetPath)
            return false
        }

        switch header.Typeflag {
        case tar.TypeDir:
            // Create directory
            if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
                log.Println("Error creating directory:", err)
                return false
            }
        case tar.TypeReg:
            // Create file
            outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
            if err != nil {
                log.Println("Error creating file:", err)
                return false
            }
            defer outFile.Close() // Ensure the file is closed properly
            if _, err := io.Copy(outFile, tarReader); err != nil {
                log.Println("Error writing file:", err)
                return false
            }
        default:
            log.Println("Unknown type of file in tar archive:", header.Typeflag)
            return false
        }
    }

    return true
}

// isSafePath checks if the provided path is within the allowed base directory
func isSafePath(path string) bool {
    // Define a base directory for safe extraction
    baseDir := "/safe/base/directory"
    // Get the absolute path
    absPath, err := filepath.Abs(path)
    if err != nil {
        log.Println("Error getting absolute path:", err)
        return false
    }
    // Check if the absolute path starts with the base directory
    return filepath.HasPrefix(absPath, baseDir)
}