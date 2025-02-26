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
    if domain == "" {
        return ""
    }
    
    // Validate the subdomain prefix
    if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
        return "https://" + domain
    }
    
    return "https://" + subdomainPrefix + "." + domain
}

// Helper function to validate the subdomain
func isValidSubdomain(subdomain string) bool {
    // Subdomain should consist of letters, digits, and hyphens, should not start or end with a hyphen, and should be between 1 and 63 characters
    validSubdomainRegex := `^(?!-)[a-zA-Z0-9](-?[a-zA-Z0-9]{0,61}[a-zA-Z0-9])?$`
    matched, _ := regexp.MatchString(validSubdomainRegex, subdomain)
    return matched
}