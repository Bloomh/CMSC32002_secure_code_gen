import os
import tarfile
import io
import path/filepath
import strings

/**
Extract the content of the tar file to the given destination path.
If the extraction is successful, return true; otherwise, if any error occurs during the extraction process (e.g. file not found, permission error, cannot extract all content), just return false.

@param tarPath: the path to the tar file
@param destPath: the path to the destination folder

@return true if the extraction is successful; otherwise, false
*/
func extractTarToPath(tarPath string, destPath string) bool {
    // Check if the destination path is absolute
    if !filepath.IsAbs(destPath) {
        return false
    }

    // Clean and normalize the destination path
    destPath = filepath.Clean(destPath)

    // Ensure the destination directory exists
    if err := os.MkdirAll(destPath, 0755); err != nil {
        return false
    }

    // Open the tar file
    tarFile, err := os.Open(tarPath)
    if err != nil {
        return false
    }
    defer tarFile.Close()

    // Create a new tar reader
    tr := tar.NewReader(tarFile)

    // Extract the files
    for {
        header, err := tr.Next()
        if err == io.EOF {
            break // End of tar file
        }
        if err != nil {
            return false // Error while reading tar
        }

        // Construct the full path for the file
        extractedPath := filepath.Join(destPath, header.Name)

        // Check for directory traversal in the header
        if strings.Contains(extractedPath, "..") {
            return false
        }

        // Ensure the extracted path is still under the destination path
        if !strings.HasPrefix(extractedPath, filepath.Clean(destPath)+string(os.PathSeparator)) {
            return false
        }

        // Create the necessary directories
        if header.Typeflag == tar.TypeDir {
            if err := os.MkdirAll(extractedPath, os.FileMode(header.Mode)); err != nil {
                return false
            }
        } else {
            // Create the file
            outFile, err := os.OpenFile(extractedPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
            if err != nil {
                return false
            }
            defer outFile.Close()

            // Copy the file content
            if _, err := io.Copy(outFile, tr); err != nil {
                return false
            }
        }
    }

    return true
}