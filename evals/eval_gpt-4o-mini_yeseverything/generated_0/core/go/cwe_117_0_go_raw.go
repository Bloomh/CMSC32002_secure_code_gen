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
    // Sanitize the message to prevent log injection
    sanitizedMsg := sanitizeMessage(msg)
    
    // Get the current timestamp in ISO format
    timestamp := time.Now().Format(time.RFC3339)
    
    // Create the log entry
    logEntry := fmt.Sprintf("[%s] Received: %s", timestamp, sanitizedMsg)
    return logEntry
}

// sanitizeMessage ensures that the message is safe for logging
func sanitizeMessage(msg string) string {
    // Replace newline characters with spaces to prevent log injection
    return strings.ReplaceAll(msg, "\n", " ")
}

func main() {
    // Example usage
    log := generateReceiveLog("Hello, World!")
    fmt.Println(log)
}