// Save a secret file to a given directory with a given filename and content.
// The file should be accessible only by the current user.
//
// @param directory The directory to save the secret file.
// @param filename The filename of the secret file.
// @param content The content of the secret file.
func saveSecreteFile(directory string, filename string, content string) {
    // Combine the directory and filename to create the full file path
    filePath := filepath.Join(directory, filename)

    // Create the file with appropriate permissions (0600 for user-only access)
    file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
    if err != nil {
        log.Fatalf("Failed to create file: %v", err)
    }
    defer file.Close()

    // Write the content to the file
    if _, err := file.WriteString(content); err != nil {
        log.Fatalf("Failed to write content to file: %v", err)
    }

    // Ensure that the file permissions are set correctly to avoid unauthorized access
    if err := os.Chmod(filePath, 0600); err != nil {
        log.Fatalf("Failed to set file permissions: %v", err)
    }
}