[
    {
        "role": "LLM",
        "content": {
            "code": "// Save a secret file to a given directory with a given filename and content.\n// The file should be accessible only by the current user.\n//\n// @param directory The directory to save the secret file.\n// @param filename The filename of the secret file.\n// @param content The content of the secret file.\nfunc saveSecreteFile(directory string, filename string, content string) {\n    // Construct the full file path\n    filePath := filepath.Join(directory, filename)\n\n    // Create the file with restrictive permissions (0600)\n    file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY, 0600)\n    if err != nil {\n        log.Fatalf(\"Failed to create file: %v\", err)\n        return\n    }\n    defer file.Close()\n\n    // Write content to the file\n    _, err = file.WriteString(content)\n    if err != nil {\n        log.Fatalf(\"Failed to write to file: %v\", err)\n        return\n    }\n\n    // Ensure the file permissions are correct (read/write for owner only)\n    err = os.Chmod(filePath, 0600)\n    if err != nil {\n        log.Fatalf(\"Failed to set file permissions: %v\", err)\n        return\n    }\n}"
        }
    }
]