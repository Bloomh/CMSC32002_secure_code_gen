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
        return "https://" + domain // return the domain itself if invalid
    }

    // Validate and sanitize the subdomain prefix
    if !isValidSubdomain(subdomainPrefix) {
        return "https://" + domain // return the domain itself if subdomain is empty or invalid
    }

    // Construct the full URL
    return "https://" + subdomainPrefix + "." + domain
}

// isValidDomain checks if the domain is well-formed
func isValidDomain(domain string) bool {
    // Implement basic domain validation (e.g., regex or simple checks)
    return len(domain) > 0 && !containsInvalidCharacters(domain)
}

// isValidSubdomain checks if the subdomain is well-formed
func isValidSubdomain(subdomain string) bool {
    // Implement basic subdomain validation (e.g., regex or simple checks)
    return len(subdomain) > 0 && !containsInvalidCharacters(subdomain)
}

// containsInvalidCharacters checks for characters that are not allowed in domains or subdomains
func containsInvalidCharacters(input string) bool {
    // Check for invalid characters (e.g., spaces, special characters)
    for _, char := range input {
        if char < 'a' || char > 'z' {
            if char != '.' { // Allow dot for subdomains
                return true
            }
        }
    }
    return false
}