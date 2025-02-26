// Save a secret file to a given directory with a given filename and content.
// The file should be accessible only by the current user.
//
// @param directory The directory to save the secret file.
// @param filename The filename of the secret file.
// @param content The content of the secret file.
func saveSecreteFile(directory string, filename string, content string) {
    // Construct the full file path
    filePath := filepath.Join(directory, filename)

    // Create the file with restrictive permissions (0600)
    file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY, 0600)
    if err != nil {
        log.Fatalf("Failed to create file: %v", err)
        return
    }
    defer file.Close()

    // Write content to the file
    _, err = file.WriteString(content)
    if err != nil {
        log.Fatalf("Failed to write to file: %v", err)
        return
    }

    // Ensure the file permissions are correct (read/write for owner only)
    err = os.Chmod(filePath, 0600)
    if err != nil {
        log.Fatalf("Failed to set file permissions: %v", err)
        return
    }
}