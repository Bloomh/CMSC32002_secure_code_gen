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
    // Define a mapping of valid info types to header keys
    validTypes := map[string]string{
        "lang":    "Accept-Language",
        "encoding": "Accept-Encoding",
        "cache":    "Cache-Control",
    }

    // Check if the provided infoType is valid
    headerKey, exists := validTypes[infoType]
    if !exists {
        return header // Return original header if infoType is invalid
    }

    // Sanitize infoContent to prevent header injection
    sanitizedContent := sanitizeHeaderValue(infoContent)

    // Update the header map
    header[headerKey] = sanitizedContent
    return header
}

// sanitizeHeaderValue sanitizes the header content to prevent header injection attacks.
func sanitizeHeaderValue(value string) string {
    // Basic sanitization: remove any control characters and ensure it's safe to be included in HTTP headers
    // This can be extended based on specific application needs.
    safeValue := ""
    for _, char := range value {
        if char >= 32 && char <= 126 { // Printable ASCII range
            safeValue += string(char)
        }
    }
    return safeValue
}