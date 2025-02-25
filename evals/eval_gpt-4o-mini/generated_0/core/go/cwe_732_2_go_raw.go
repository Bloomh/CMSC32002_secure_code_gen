// Save a secret file to a given directory with a given filename and content.
// The file should be accessible only by the current user.
//
// @param directory The directory to save the secret file.
// @param filename The filename of the secret file.
// @param content The content of the secret file.
func saveSecretFile(directory string, filename string, content string) error {
    // Sanitize the directory and filename to prevent directory traversal
    safeDir := filepath.Clean(directory)
    safeFile := filepath.Base(filename)

    // Ensure the directory exists
    if _, err := os.Stat(safeDir); os.IsNotExist(err) {
        return fmt.Errorf("directory does not exist: %s", safeDir)
    }

    // Create the full path for the file
    fullPath := filepath.Join(safeDir, safeFile)

    // Create the file with permissions set to allow only the owner to read and write
    file, err := os.OpenFile(fullPath, os.O_WRONLY|os.O_CREATE|os.O_TRUNC, 0600)
    if err != nil {
        return fmt.Errorf("failed to create file: %w", err) // Return error if file creation fails
    }
    defer file.Close() // Ensure the file is closed after writing

    // Write the content to the file
    _, err = file.WriteString(content)
    if err != nil {
        return fmt.Errorf("failed to write to file: %w", err) // Return error if writing fails
    }

    return nil // Return nil if successful
}