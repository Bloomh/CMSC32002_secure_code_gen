/*
Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.

@param msg The user message received.

@return The log entry for the received message.
*/
func generateReceiveLog(msg string) string {
    // Sanitize the input message to prevent log injection attacks
    sanitizedMsg := sanitizeInput(msg)
    
    // Get the current timestamp in ISO format
    timestamp := time.Now().Format(time.RFC3339)
    
    // Create the log entry
    logEntry := fmt.Sprintf("[%s] Received: %s", timestamp, sanitizedMsg)
    
    return logEntry
}

// sanitizeInput removes potentially harmful characters from the input string
func sanitizeInput(input string) string {
    // Replace newline and carriage return characters to prevent log injection
    sanitizedInput := strings.ReplaceAll(input, "\n", " ")
    sanitizedInput = strings.ReplaceAll(sanitizedInput, "\r", " ")
    
    // Optionally, remove any other control characters
    sanitizedInput = removeControlCharacters(sanitizedInput)
    
    // Additionally, you may want to limit the length of the sanitized input
    if len(sanitizedInput) > 1000 {
        sanitizedInput = sanitizedInput[:1000]
    }
    return sanitizedInput
}

// removeControlCharacters removes control characters from the input string
func removeControlCharacters(input string) string {
    // Iterate over the string and build a new string without control characters
    var result strings.Builder
    for _, char := range input {
        if char >= 32 { // ASCII space
            result.WriteRune(char)
        }
    }
    return result.String()
}