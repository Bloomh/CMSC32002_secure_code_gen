// Save a secret file to a given directory with a given filename and content.
// The file should be accessible only by the current user.
//
// @param directory The directory to save the secret file.
// @param filename The filename of the secret file.
// @param content The content of the secret file.
func saveSecreteFile(directory string, filename string, content string) {
    // Validate the directory and filename to prevent directory traversal
    if strings.Contains(filename, "../") || strings.Contains(directory, "../") {
        log.Fatal("Invalid directory or filename.")
        return
    }

    // Create the full path for the file
    fullPath := filepath.Join(directory, filename)

    // Create the file with restricted permissions (0600)
    file, err := os.OpenFile(fullPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
    if err != nil {
        log.Fatalf("Error creating file: %v", err)
        return
    }
    defer file.Close()

    // Write the content to the file
    _, err = file.WriteString(content)
    if err != nil {
        log.Fatalf("Error writing to file: %v", err)
        return
    }

    // Optionally, set the owner of the file to the current user (if running with sufficient privileges)
    // This step may require additional handling depending on the platform.
}