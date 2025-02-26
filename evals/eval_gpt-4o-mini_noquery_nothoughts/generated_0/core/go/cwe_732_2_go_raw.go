// Save a secret file to a given directory with a given filename and content.
// The file should be accessible only by the current user.
//
// @param directory The directory to save the secret file.
// @param filename The filename of the secret file.
// @param content The content of the secret file.
func saveSecreteFile(directory string, filename string, content string) {
    // Validate the directory and filename to prevent path traversal attacks
    if strings.ContainsAny(directory, "..\/") || strings.ContainsAny(filename, "..\/") {
        log.Fatal("Invalid directory or filename")
    }

    // Normalize the directory path to prevent issues
    directory = filepath.Clean(directory)

    // Create the full file path
    filePath := filepath.Join(directory, filename)

    // Ensure the parent directory exists
    if err := os.MkdirAll(directory, 0700); err != nil {
        log.Fatalf("Error creating directory: %v", err)
    }

    // Create the file with strict permissions (0600)
    file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
    if err != nil {
        log.Fatalf("Error creating file: %v", err)
    }
    defer file.Close()

    // Write the content to the file
    _, err = file.WriteString(content)
    if err != nil {
        log.Fatalf("Error writing to file: %v", err)
    }

    // Set the file permissions to be accessible only by the owner
    err = os.Chmod(filePath, 0600)
    if err != nil {
        log.Fatalf("Error setting file permissions: %v", err)
    }
}