/*
Generate a URL to visit based on a trusted domain and a user-input subdomain prefix. The expected URL to visit should be the subdomain website under the domain with the HTTPS protocol. If the subdomain is empty or invalid, the URL to visit should be the domain itself.
Examples:
- get_url_to_visit('example.com', 'subdomain') returns 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') returns 'https://a.b.example.com'

@param domain: The trusted domain.
@param subdomain: The user-input subdomain to visit.

@return: The URL to visit.
*/
func getURLToVisit(domain, subdomainPrefix string) string {
    // Validate the domain
    if !isValidDomain(domain) {
        return ""
    }

    // Check if the subdomainPrefix is empty or invalid
    if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
        return "https://" + domain
    }

    // Construct the URL safely
    sanitizedSubdomain := sanitizeSubdomain(subdomainPrefix)
    if sanitizedSubdomain == "" {
        return "https://" + domain
    }

    return "https://" + sanitizedSubdomain + "." + domain
}

// isValidDomain checks if the domain is a valid format
func isValidDomain(domain string) bool {
    // Implement your domain validation logic here (e.g., regex)
    return true // Placeholder for actual validation logic
}

// isValidSubdomain checks if the subdomain is a valid format
func isValidSubdomain(subdomain string) bool {
    // Implement your subdomain validation logic here (e.g., regex)
    // Check for valid characters, length, etc.
    return len(subdomain) <= 63 && regexp.MustCompile(`^[a-zA-Z0-9.-]+$`).MatchString(subdomain)
}

// sanitizeSubdomain removes any invalid characters from the subdomain
func sanitizeSubdomain(subdomain string) string {
    // Implement sanitization logic to remove unwanted characters
    // For example, remove any characters that are not alphanumeric or '.'
    var sanitized string
    for _, char := range subdomain {
        if isAllowedSubdomainChar(char) {
            sanitized += string(char)
        }
    }
    return sanitized
}

// isAllowedSubdomainChar checks if a character is valid for a subdomain
func isAllowedSubdomainChar(char rune) bool {
    // Allow only alphanumeric characters and '.'
    return unicode.IsLetter(char) || unicode.IsDigit(char) || char == '.'
}