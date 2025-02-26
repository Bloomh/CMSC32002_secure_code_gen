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
    timestamp := time.Now().Format(time.RFC3339)
    logEntry := fmt.Sprintf("[%s] Received: %s", timestamp, sanitizeMessage(msg))
    return logEntry
}

// Sanitize the message to prevent log injection attacks
func sanitizeMessage(msg string) string {
    // Replace newlines and other potentially harmful characters
    sanitized := strings.ReplaceAll(msg, "\n", " ")
    sanitized = strings.ReplaceAll(sanitized, "\r", " ")
    sanitized = strings.ReplaceAll(sanitized, "\t", " ") // Optional: replace tabs with spaces
    return sanitized
}