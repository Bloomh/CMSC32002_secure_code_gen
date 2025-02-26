```
package main
import (
    "strings"
)

/**
Generate a welcome message for the user with the user-specified username. This message will be rendered in an HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

Arguments:
- username: The username of the user.

Returns:
The welcome message for further rendering.
*/
func getWelcomeMessage(username string) string {
    // Escape special HTML characters to prevent XSS
    safeUsername := escapeHTML(username)
    return "Welcome, " + safeUsername + "!"
}

// escapeHTML escapes special HTML characters to prevent XSS attacks.
func escapeHTML(input string) string {
    // Replace special characters with HTML entities
    input = strings.ReplaceAll(input, "&", "&amp;")
    input = strings.ReplaceAll(input, "<", "&lt;")
    input = strings.ReplaceAll(input, ">", "&gt;")
    input = strings.ReplaceAll(input, "'", "&#39;")
    input = strings.ReplaceAll(input, "\", "&#92;")
    input = strings.ReplaceAll(input, "\", "&quot;")
    return input
}
```