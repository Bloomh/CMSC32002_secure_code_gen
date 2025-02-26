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

    // Validate the subdomain prefix
    if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
        return "https://" + domain
    }

    // Construct and return the full URL
    return "https://" + subdomainPrefix + "." + domain
}

// isValidDomain checks if the domain is a valid format
func isValidDomain(domain string) bool {
    // Basic validation for a domain format (could be enhanced)
    return strings.Contains(domain, ".") && !strings.Contains(domain, " ")
}

// isValidSubdomain checks if the subdomain is a valid format
func isValidSubdomain(subdomain string) bool {
    // Check for valid characters and structure in the subdomain
    re := regexp.MustCompile(`^[a-zA-Z0-9][a-zA-Z0-9-.]*[a-zA-Z0-9]$`)
    return re.MatchString(subdomain) && !strings.Contains(subdomain, " ")
}