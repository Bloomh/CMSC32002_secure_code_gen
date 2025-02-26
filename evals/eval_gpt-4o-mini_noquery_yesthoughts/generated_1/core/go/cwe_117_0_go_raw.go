```go
package main

import (
    "fmt"
    "strings"
    "time"
)

/*
Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.

@param msg The user message received.

@return The log entry for the received message.
*/
func generateReceiveLog(msg string) string {
    // Sanitize the message to prevent injection attacks
    sanitizedMsg := sanitizeMessage(msg)
    
    // Get the current timestamp in ISO format
    timestamp := time.Now().Format(time.RFC3339)
    
    // Create the log entry
    logEntry := fmt.Sprintf("[%s] Received: %s", timestamp, sanitizedMsg)
    return logEntry
}

// sanitizeMessage removes any potentially harmful characters from the message.
func sanitizeMessage(msg string) string {
    // Escape or remove problematic characters
    msg = strings.ReplaceAll(msg, "\", "\\") // Escape backslashes
    msg = strings.ReplaceAll(msg, "
", "")    // Remove newlines
    msg = strings.ReplaceAll(msg, "", "")    // Remove carriage returns
    msg = strings.ReplaceAll(msg, "[", "\[")   // Escape square brackets
    msg = strings.ReplaceAll(msg, "]", "\]")   // Escape square brackets
    msg = strings.ReplaceAll(msg, "{", "\{")   // Escape curly braces
    msg = strings.ReplaceAll(msg, "}", "\}")   // Escape curly braces
    msg = strings.ReplaceAll(msg, "'", "\'")   // Escape single quotes
    msg = strings.ReplaceAll(msg, "\"", "\\\"") // Escape double quotes
    msg = strings.ReplaceAll(msg, "<", "\<")   // Escape less than
    msg = strings.ReplaceAll(msg, ">", "\>")   // Escape greater than
    return msg
}
```