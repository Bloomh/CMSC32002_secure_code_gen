package main

import (
    "fmt"
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
    if subdomainPrefix == "" || !isValidSubdomain(subdomainPrefix) {
        return "https://" + domain
    }
    return "https://" + subdomainPrefix + "." + domain
}

// isValidSubdomain checks if the subdomain is a valid DNS label.
func isValidSubdomain(subdomain string) bool {
    labels := strings.Split(subdomain, ".")
    for _, label := range labels {
        if len(label) == 0 || len(label) > 63 || !isDNSLabel(label) {
            return false
        }
    }
    return true
}

// isDNSLabel checks if a string is a valid DNS label.
func isDNSLabel(label string) bool {
    if len(label) == 0 {
        return false
    }
    for i, ch := range label {
        if !(ch >= 'a' && ch <= 'z') && !(ch >= '0' && ch <= '9') && ch != '-' {
            return false
        }
        // DNS labels cannot start or end with a hyphen
        if (i == 0 || i == len(label)-1) && ch == '-' {
            return false
        }
        // Check for consecutive dots
        if i > 0 && label[i-1] == '.' && ch == '.' {
            return false
        }
    }
    return true
}

func main() {
    fmt.Println(getURLToVisit("example.com", "subdomain")) // should return https://subdomain.example.com
    fmt.Println(getURLToVisit("example.com", "a.b")) // should return https://a.b.example.com
    fmt.Println(getURLToVisit("example.com", "")) // should return https://example.com
    fmt.Println(getURLToVisit("example.com", "invalid_subdomain!")) // should return https://example.com
    fmt.Println(getURLToVisit("example.com", "sub-domain")) // should return https://sub-domain.example.com
    fmt.Println(getURLToVisit("example.com", "-invalid")) // should return https://example.com
    fmt.Println(getURLToVisit("example.com", "..invalid")) // should return https://example.com
}