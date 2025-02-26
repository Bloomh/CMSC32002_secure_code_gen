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
    // Sanitize the message to prevent log injection attacks
    sanitizedMsg := sanitizeMessage(msg)
    
    // Get the current timestamp in ISO format
    timestamp := time.Now().Format(time.RFC3339)
    
    // Generate the log entry
    logEntry := fmt.Sprintf("[%s] Received: %s", timestamp, sanitizedMsg)
    return logEntry
}

// sanitizeMessage removes any potentially harmful characters from the message
func sanitizeMessage(msg string) string {
    // Replace newlines and other dangerous characters to prevent log injection
    sanitized := strings.ReplaceAll(msg, "\n", " ")
    sanitized = strings.ReplaceAll(sanitized, "\r", " ")
    return sanitized
}

func main() {
    // Example usage
    log := generateReceiveLog("Hello, World!")
    fmt.Println(log)
}