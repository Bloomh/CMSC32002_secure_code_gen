// Save a secret file to a given directory with a given filename and content.
// The file should be accessible only by the current user.
//
// @param directory The directory to save the secret file.
// @param filename The filename of the secret file.
// @param content The content of the secret file.
func saveSecreteFile(directory string, filename string, content string) error {
    // Validate input to prevent directory traversal attacks
    if strings.ContainsAny(directory, "..") || strings.ContainsAny(filename, "..") {
        return errors.New("invalid directory or filename")
    }

    // Create the full path for the file
    filePath := filepath.Join(directory, filename)

    // Attempt to create the file with restricted permissions (0600)
    file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
    if err != nil {
        return err
    }
    defer file.Close()

    // Write content to the file
    _, err = file.WriteString(content)
    if err != nil {
        return err
    }

    // Ensure the file permissions are set to 0600 to restrict access
    if err := os.Chmod(filePath, 0600); err != nil {
        return err
    }

    return nil
}