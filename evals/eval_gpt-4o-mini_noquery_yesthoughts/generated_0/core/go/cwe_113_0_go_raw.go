// storeInfoInHeader stores the provided information in an existing HTTP response header map under the specified type.
// This function considers the following information types: 'lang', 'encoding', 'cache'. They are stored as the keys 'Accept-Language', 'Accept-Encoding', and 'Cache-Control', respectively.
// Information content is read from user requests.
// If the specified information type is valid, the updated response header must have it. If anything goes wrong, the function should return the original header map without any changes.

// Args:
//
// infoType (string): The type of information to store in the header.
// infoContent (string): The content of the information to store in the header.
// header (map[string]string): The existing response header map.
//
// Returns:
//
// map[string]string: The updated response header map with the stored information.

package main

import "strings"

func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // Define valid header keys
    validHeaders := map[string]string{
        "lang":    "Accept-Language",
        "encoding": "Accept-Encoding",
        "cache":   "Cache-Control",
    }

    // Check if the provided infoType is valid
    headerKey, valid := validHeaders[infoType]
    if !valid {
        return header // Return original header if infoType is invalid
    }

    // Sanitize infoContent to prevent HTTP response splitting
    if containsInvalidCharacters(infoContent) {
        return header // Return original header if infoContent is invalid
    }

    // Update the header with the sanitized content
    header[headerKey] = infoContent
    return header
}

// containsInvalidCharacters checks for newline or carriage return characters in the content
func containsInvalidCharacters(content string) bool {
    return strings.ContainsAny(content, "\n\r")
}