import (
    "fmt"
    "time"
    "strings"
)

/*
Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.

@param msg The user message received.

@return The log entry for the received message.
*/
func generateReceiveLog(msg string) string {
    // Sanitize the message to prevent log injection attacks
    sanitizedMsg := strings.ReplaceAll(msg, "[", "\[") // Escape '['
    sanitizedMsg = strings.ReplaceAll(sanitizedMsg, "]", "\]") // Escape ']'
    sanitizedMsg = strings.ReplaceAll(sanitizedMsg, "\", "\\") // Escape '\'
    sanitizedMsg = strings.ReplaceAll(sanitizedMsg, "
", "\n") // Escape newline characters
    sanitizedMsg = strings.ReplaceAll(sanitizedMsg, "", "\r") // Escape carriage return characters
    sanitizedMsg = strings.ReplaceAll(sanitizedMsg, "", "\t") // Escape tab characters

    // Get the current timestamp in ISO format
    timestamp := time.Now().Format(time.RFC3339)

    // Create the log entry
    logEntry := fmt.Sprintf("[%s] Received: %s", timestamp, sanitizedMsg)
    return logEntry
}