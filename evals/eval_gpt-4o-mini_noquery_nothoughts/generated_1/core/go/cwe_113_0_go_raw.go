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
    // Validate the input to prevent header injection attacks
    if infoContent == "" {
        return header // Return original header if content is empty
    }

    // Sanitize the infoContent to prevent any malicious input
    sanitizedContent := sanitizeInput(infoContent)

    // Check for valid infoType and update the header accordingly
    switch infoType {
    case "lang":
        header["Accept-Language"] = sanitizedContent
    case "encoding":
        header["Accept-Encoding"] = sanitizedContent
    case "cache":
        header["Cache-Control"] = sanitizedContent
    default:
        return header // Return original header if infoType is invalid
    }

    // Return the updated header map
    return header
}

// sanitizeInput is a helper function to sanitize user input to prevent header injection
func sanitizeInput(input string) string {
    // Replace invalid characters and trim whitespace
    // This regex allows alphanumeric characters, dashes, underscores, spaces, and commas
    return strings.TrimSpace(regexp.MustCompile(`[^a-zA-Z0-9-_, ]`).ReplaceAllString(input, ""))
}