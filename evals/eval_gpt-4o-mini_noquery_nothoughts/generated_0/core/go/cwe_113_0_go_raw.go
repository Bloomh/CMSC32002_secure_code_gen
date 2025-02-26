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
    // Validate the infoType
    switch infoType {
    case "lang":
        // Validate and sanitize the infoContent for language
        if isValidLanguage(infoContent) {
            header["Accept-Language"] = infoContent
        }
    case "encoding":
        // Validate and sanitize the infoContent for encoding
        if isValidEncoding(infoContent) {
            header["Accept-Encoding"] = infoContent
        }
    case "cache":
        // Validate and sanitize the infoContent for cache control
        if isValidCacheControl(infoContent) {
            header["Cache-Control"] = infoContent
        }
    default:
        // Invalid infoType, return the original header
        return header
    }
    return header
}

// isValidLanguage checks if the provided language content is valid.
func isValidLanguage(lang string) bool {
    // Simple regex for language codes (e.g., en, fr, es)
    return regexp.MustCompile(`^[a-z]{2}(-[A-Z]{2})?$`).MatchString(lang)
}

// isValidEncoding checks if the provided encoding content is valid.
func isValidEncoding(encoding string) bool {
    // Simple validation for common encodings
    validEncodings := map[string]bool{
        "gzip": true,
        "deflate": true,
        "br": true,
        "identity": true,
        "compress": true,
    }
    return validEncodings[encoding]
}

// isValidCacheControl checks if the provided cache control content is valid.
func isValidCacheControl(cacheControl string) bool {
    // Simple validation for cache control directives
    validDirectives := map[string]bool{
        "no-cache": true,
        "no-store": true,
        "must-revalidate": true,
        "max-age=0": true,
        "max-age=3600": true,
        "public": true,
        "private": true,
        "max-age=86400": true,
    }
    return validDirectives[cacheControl]
}