package main

import (
    "fmt"
    "net"
    "regexp"
    "strings"
)

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

    // Construct the URL
    return "https://" + subdomainPrefix + "." + domain
}

// isValidDomain checks if the domain is valid
func isValidDomain(domain string) bool {
    // Simple validation: check if the domain contains at least one dot
    return strings.Count(domain, ".") > 0
}

// isValidSubdomain checks if the subdomain is valid
func isValidSubdomain(subdomain string) bool {
    // Use regex to check for valid subdomain characters
    // Valid characters: letters, digits, hyphens, and must not start or end with a hyphen
    validSubdomain := regexp.MustCompile(`^(?!-)([a-zA-Z0-9][-a-zA-Z0-9]{0,61}[a-zA-Z0-9]?)(\.[a-zA-Z0-9][-a-zA-Z0-9]{0,61}[a-zA-Z0-9]?)*$`)
    return len(subdomain) > 0 && validSubdomain.MatchString(subdomain)
}

func main() {
    fmt.Println(getURLToVisit("example.com", "subdomain")) // Output: https://subdomain.example.com
    fmt.Println(getURLToVisit("example.com", "a.b"))      // Output: https://a.b.example.com
    fmt.Println(getURLToVisit("example.com", ""))         // Output: https://example.com
    fmt.Println(getURLToVisit("example.com", "invalid@sub")) // Output: https://example.com
    fmt.Println(getURLToVisit("example.com", "-invalid")) // Output: https://example.com
    fmt.Println(getURLToVisit("example.com", "valid-subdomain")) // Output: https://valid-subdomain.example.com
}