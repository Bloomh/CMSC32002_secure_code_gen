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
    // Validate and clean the destination path
    destPath, err := filepath.Abs(destPath)
    if err != nil {
        log.Println("Error determining absolute path:", err)
        return false
    }

    // Open the tar file
    file, err := os.Open(tarPath)
    if err != nil {
        log.Println("Error opening tar file:", err)
        return false
    }
    defer file.Close()

    // Create a new tar reader
    tarReader := tar.NewReader(file)

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

        // Create the full path for the extracted file
        extractedPath := filepath.Join(destPath, header.Name)

        // Prevent directory traversal attacks
        if !filepath.HasPrefix(extractedPath, destPath) {
            log.Println("Attempted directory traversal:", header.Name)
            return false
        }

        // Handle directory creation
        if header.Typeflag == tar.TypeDir {
            if err := os.MkdirAll(extractedPath, os.ModePerm); err != nil {
                log.Println("Error creating directory:", err)
                return false
            }
            continue
        }

        // Create the file
        outFile, err := os.OpenFile(extractedPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0644)
        if err != nil {
            log.Println("Error creating file:", err)
            return false
        }
        defer outFile.Close()

        // Copy the contents of the tar entry to the file
        if _, err := io.Copy(outFile, tarReader); err != nil {
            log.Println("Error extracting file:", err)
            return false
        }
    }

    return true
}