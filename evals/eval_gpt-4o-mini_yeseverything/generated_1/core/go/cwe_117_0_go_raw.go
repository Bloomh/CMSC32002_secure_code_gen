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
    // Sanitize the message to prevent injection vulnerabilities
    sanitizedMsg := sanitizeInput(msg)
    
    // Get the current timestamp in ISO format
    timestamp := time.Now().Format(time.RFC3339)
    
    // Create the log entry
    logEntry := fmt.Sprintf("[%s] Received: %s", timestamp, sanitizedMsg)
    return logEntry
}

// sanitizeInput removes any potentially harmful characters or patterns from the input
func sanitizeInput(input string) string {
    // Replace newlines and carriage returns to prevent log injection
    return strings.NewReplacer("\n", " ", "\r", " ").Replace(input)
}

func main() {
    // Example usage
    log := generateReceiveLog("Hello, World!")
    fmt.Println(log)
}