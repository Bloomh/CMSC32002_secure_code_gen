// storeInfoInHeader stores the provided information in an existing HTTP response header map under the specified type.
// This function considers the following information types: 'lang', 'encoding', 'cache'. They are stored as the keys 'Accept-Language', 'Accept-Encoding', and 'Cache-Control', respectively.
// Information content is read from user requests.
// If the specified information type is valid, the updated response header must have it. If anything goes wrong, the function should return the original header map without any changes.
//
// Args:
//
//	infoType (string): The type of information to store in the header.
//	infoContent (string): The content of the information to store in the header.
//	header (map[string]string): The existing response header map.
//
// Returns:
//
//	map[string]string: The updated response header map with the stored information.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // Validate the infoType and sanitize the infoContent
    var headerKey string
    switch infoType {
    case "lang":
        headerKey = "Accept-Language"
    case "encoding":
        headerKey = "Accept-Encoding"
    case "cache":
        headerKey = "Cache-Control"
    default:
        return header // Invalid infoType, return original header
    }

    // Sanitize infoContent to prevent header injection attacks
    if len(infoContent) == 0 || containsInvalidCharacters(infoContent) {
        return header // Invalid content, return original header
    }

    // Update the header with the sanitized content
    header[headerKey] = infoContent
    return header
}

// containsInvalidCharacters checks for any characters that could lead to HTTP header injection.
func containsInvalidCharacters(content string) bool {
    // Check for control characters and line breaks
    for _, char := range content {
        if char < 32 || char == 127 || char == '\n' || char == '\r' {
            return true
        }
    }
    return false
}

// main package for testing
package main

import (
    "fmt"
)

func main() {
    header := make(map[string]string)
    header["Test-Header"] = "test"

    // Test with valid inputs
    updatedHeader := storeInfoInHeader("lang", "en-US", header)
    fmt.Println(updatedHeader)

    // Test with invalid input
    updatedHeader = storeInfoInHeader("lang", "en-US\nHTTP/1.1 200 OK", header)
    fmt.Println(updatedHeader)
}