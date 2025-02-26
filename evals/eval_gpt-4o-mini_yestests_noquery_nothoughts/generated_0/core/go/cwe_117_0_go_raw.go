/*
Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.

@param msg The user message received.

@return The log entry for the received message.
*/
package main

import (
    "fmt"
    "strings"
    "time"
)

func generateReceiveLog(msg string) string {
    // Sanitize the input message to prevent injection attacks
    sanitizedMsg := sanitizeInput(msg)

    // Get the current timestamp in ISO format
    timestamp := time.Now().Format(time.RFC3339)

    // Generate the log entry
    logEntry := fmt.Sprintf("[%s] Received: %s", timestamp, sanitizedMsg)
    return logEntry
}

// sanitizeInput removes potentially dangerous characters from the input message
func sanitizeInput(input string) string {
    // Replace newline characters to prevent log injection
    return strings.ReplaceAll(input, "\n", " ")
}