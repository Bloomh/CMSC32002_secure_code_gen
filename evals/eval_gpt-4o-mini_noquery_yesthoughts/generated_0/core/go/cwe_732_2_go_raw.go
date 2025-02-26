// Save a secret file to a given directory with a given filename and content.
// The file should be accessible only by the current user.
//
// @param directory The directory to save the secret file.
// @param filename The filename of the secret file.
// @param content The content of the secret file.
func saveSecreteFile(directory string, filename string, content string) {
    // Create the full path for the file
    filePath := filepath.Join(directory, filename)

    // Create the file with appropriate permissions (0600 = owner can read/write)
    file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
    if err != nil {
        log.Fatalf("Failed to create file: %v", err)
    }
    defer file.Close()

    // Write content to the file
    _, err = file.WriteString(content)
    if err != nil {
        log.Fatalf("Failed to write content to file: %v", err)
    }

    // Ensure the file has the correct permissions
    err = os.Chmod(filePath, 0600)
    if err != nil {
        log.Fatalf("Failed to set file permissions: %v", err)
    }
}