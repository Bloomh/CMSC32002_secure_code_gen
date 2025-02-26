// Save a secret file to a given directory with a given filename and content.
// The file should be accessible only by the current user.
//
// @param directory The directory to save the secret file.
// @param filename The filename of the secret file.
// @param content The content of the secret file.
func saveSecreteFile(directory string, filename string, content string) error {
    // Create the full file path
    filePath := filepath.Join(directory, filename)

    // Create the file with restrictive permissions (0600) so only the owner can read/write
    file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
    if err != nil {
        return fmt.Errorf("failed to create file: %w", err)
    }
    defer file.Close()

    // Write the content to the file
    _, err = file.WriteString(content)
    if err != nil {
        return fmt.Errorf("failed to write to file: %w", err)
    }

    return nil
}