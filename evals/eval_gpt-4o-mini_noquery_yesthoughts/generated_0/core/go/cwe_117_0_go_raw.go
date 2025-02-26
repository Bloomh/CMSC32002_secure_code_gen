```
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
    // Get current timestamp in ISO format
    timestamp := time.Now().Format(time.RFC3339)
    
    // Sanitize the message to prevent log injection
    sanitizedMsg := strings.ReplaceAll(msg, "[", "[\[") // Escape '['
    sanitizedMsg = strings.ReplaceAll(sanitizedMsg, "]", "[\]") // Escape ']'
    sanitizedMsg = strings.ReplaceAll(sanitizedMsg, "\\", "[\\\\]") // Escape '\'
    sanitizedMsg = strings.ReplaceAll(sanitizedMsg, "\"", "[\"]") // Escape '"
    
    // Create the log entry
    logEntry := fmt.Sprintf("[%s] Received: %s", timestamp, sanitizedMsg)
    return logEntry
}
```