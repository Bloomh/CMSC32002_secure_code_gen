```
/*
Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.

@param msg The user message received.

@return The log entry for the received message.
*/
func generateReceiveLog(msg string) string {
    // Validate input to prevent empty message
    if len(msg) == 0 {
        return "[Invalid Message]"
    }

    // Sanitize the input to prevent log injection attacks
    sanitizedMsg := strings.ReplaceAll(msg, "\", "\\")
    sanitizedMsg = strings.ReplaceAll(sanitizedMsg, "[", "\[")
    sanitizedMsg = strings.ReplaceAll(sanitizedMsg, "]", "\]")
    sanitizedMsg = strings.ReplaceAll(sanitizedMsg, "\n", "\\n")
    sanitizedMsg = strings.ReplaceAll(sanitizedMsg, "\r", "\\r")
    sanitizedMsg = strings.ReplaceAll(sanitizedMsg, "\", "\\")

    // Get the current timestamp in ISO format
    timestamp := time.Now().Format(time.RFC3339)

    // Create the log entry
    logEntry := fmt.Sprintf("[%s] Received: %s", timestamp, sanitizedMsg)

    return logEntry
}
```