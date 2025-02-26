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
    // Define a map to hold the valid header keys.
    validHeaders := map[string]string{
        "lang": "Accept-Language",
        "encoding": "Accept-Encoding",
        "cache": "Cache-Control",
    }

    // Check if the provided infoType is valid.
    headerKey, isValid := validHeaders[infoType]
    if !isValid {
        return header // Return original header if infoType is invalid
    }

    // Sanitize infoContent to prevent header injection by checking for newline and control characters.
    if containsInvalidCharacters(infoContent) {
        return header // Return original header if infoContent contains invalid characters
    }

    // Update the header with the sanitized content.
    header[headerKey] = infoContent
    return header
}

// containsInvalidCharacters checks if the string contains newline characters or control characters.
func containsInvalidCharacters(s string) bool {
    return strings.ContainsAny(s, "\n\r\0\t") // Includes newline, carriage return, null, and tab characters
}