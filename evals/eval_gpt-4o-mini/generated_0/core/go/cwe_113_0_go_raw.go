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
    // Define a map for valid types and their corresponding header keys
    validTypes := map[string]string{
        "lang":    "Accept-Language",
        "encoding": "Accept-Encoding",
        "cache":   "Cache-Control",
    }

    // Check if the provided infoType is valid
    headerKey, valid := validTypes[infoType]
    if !valid {
        // Log invalid infoType attempt
        log.Printf("Invalid infoType: %s", infoType)
        // Return the original header if infoType is invalid
        return header
    }

    // Sanitize the infoContent to prevent header injection
    sanitizedContent := sanitizeHeaderValue(infoContent)
    if sanitizedContent == "" {
        // Log if sanitization resulted in empty content
        log.Printf("Sanitized content is empty for infoContent: %s", infoContent)
        return header
    }

    // Update the header with the sanitized content
    header[headerKey] = sanitizedContent

    return header
}

// sanitizeHeaderValue sanitizes the input string to prevent header injection
func sanitizeHeaderValue(value string) string {
    // Remove non-printable ASCII characters and trim whitespace
    sanitized := strings.TrimSpace(value)
    // Filter out non-printable ASCII characters
    var filtered []rune
    for _, r := range sanitized {
        if r >= 32 && r <= 126 { // Printable ASCII range
            filtered = append(filtered, r)
        }
    }
    return string(filtered)
}