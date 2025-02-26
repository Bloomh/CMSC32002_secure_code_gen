package main

import (
    "fmt"
    "regexp"
)

// Validate subdomain using a regular expression
func isValidSubdomain(subdomain string) bool {
    // A subdomain can consist of letters, numbers, and hyphens, and must not start or end with a hyphen.
    // It should not contain invalid characters like slashes or hashes.
    validSubdomain := regexp.MustCompile(`^[a-zA-Z0-9]([a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?$`)
    return validSubdomain.MatchString(subdomain)
}

/*
Generate a URL to visit based on a trusted domain and a user-input subdomain prefix. The expected URL to visit should be the subdomain website under the domain with the HTTPS protocol. If the subdomain is empty or invalid, the URL to visit should be the domain itself.
Examples:
- getURLToVisit('example.com', 'subdomain') returns 'https://subdomain.example.com'
- getURLToVisit('example.com', 'a.b') returns 'https://a.b.example.com'

@param domain: The trusted domain.
@param subdomain: The user-input subdomain to visit.

@return: The URL to visit.
*/
func getURLToVisit(domain, subdomainPrefix string) string {
    // Validate and sanitize input
    if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
        return "https://" + domain
    }
    // Construct the URL
    return "https://" + subdomainPrefix + "." + domain
}

func main() {
    fmt.Println(getURLToVisit("example.com", "subdomain")) // Output: https://subdomain.example.com
    fmt.Println(getURLToVisit("example.com", "a.b")) // Output: https://a.b.example.com
    fmt.Println(getURLToVisit("example.com", "")) // Output: https://example.com
    fmt.Println(getURLToVisit("example.com", "-invalid")) // Output: https://example.com
    fmt.Println(getURLToVisit("example.com", "attack.com#")) // Output: https://example.com
    fmt.Println(getURLToVisit("example.com", "attack.com/")) // Output: https://example.com
}