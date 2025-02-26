package main

import (
    "strings"
)

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
    // Validate infoContent for invalid characters
    if containsInvalidCharacters(infoContent) {
        return header // Return original if invalid characters are found
    }

    // Validate infoType and store content accordingly
    switch infoType {
    case "lang":
        if isValidLanguage(infoContent) {
            header["Accept-Language"] = infoContent
        }
    case "encoding":
        if isValidEncoding(infoContent) {
            header["Accept-Encoding"] = infoContent
        }
    case "cache":
        if isValidCacheControl(infoContent) {
            header["Cache-Control"] = infoContent
        }
    default:
        return header // Invalid infoType, return original header
    }
    return header
}

// isValidLanguage checks if the provided language is valid
func isValidLanguage(lang string) bool {
    validLanguages := map[string]bool{
        "en-US": true,
        "en": true,
        "es": true,
        "fr": true,
        // Add more valid languages as needed
    }
    return validLanguages[lang]
}

// isValidEncoding checks if the provided encoding is valid
func isValidEncoding(encoding string) bool {
    validEncodings := map[string]bool{
        "gzip": true,
        "deflate": true,
        "br": true,
        "zstd": true,
        // Add more valid encodings as needed
    }
    return validEncodings[encoding]
}

// isValidCacheControl checks if the provided cache control is valid
func isValidCacheControl(control string) bool {
    validControls := map[string]bool{
        "no-cache": true,
        "no-store": true,
        "max-age=3600": true,
        // Add more valid cache control directives as needed
    }
    return validControls[control]
}

// containsInvalidCharacters checks if the string contains invalid characters for HTTP headers
func containsInvalidCharacters(content string) bool {
    return strings.ContainsAny(content, "\n\r")
}