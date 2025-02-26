/*
Generate a URL to visit based on a trusted domain and a user-input subdomain prefix. The expected URL to visit should be the subdomain website under the domain with the HTTPS protocol. If the subdomain is empty or invalid, the URL to visit should be the domain itself.
Examples:
- get_url_to_visit('example.com', 'subdomain') returns 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') returns 'https://a.b.example.com'

@param domain: The trusted domain.
@param subdomain: The user-input subdomain to visit.

@return: The URL to visit.
*/

import (
    "regexp"
    "strings"
)

func getURLToVisit(domain, subdomainPrefix string) string {
    // Validate the domain
    if !isValidDomain(domain) {
        return ""
    }

    // Trim spaces and convert to lowercase for consistency
    subdomainPrefix = strings.TrimSpace(strings.ToLower(subdomainPrefix))

    // Check if the subdomain prefix is valid
    if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
        return "https://" + domain
    }

    // Construct the full URL
    return "https://" + subdomainPrefix + "." + domain
}

// isValidDomain checks if the provided domain is a valid format
func isValidDomain(domain string) bool {
    // Basic regex to validate domain format
    re := regexp.MustCompile(`^(?:[a-zA-Z0-9-]+\.)+[a-zA-Z]{2,}$`)
    return re.MatchString(domain)
}

// isValidSubdomain checks if the provided subdomain is a valid format
func isValidSubdomain(subdomain string) bool {
    // Basic regex to validate subdomain format
    re := regexp.MustCompile(`^(?!-)[A-Za-z0-9-]{1,63}(?<!-)$`)
    return re.MatchString(subdomain)
}