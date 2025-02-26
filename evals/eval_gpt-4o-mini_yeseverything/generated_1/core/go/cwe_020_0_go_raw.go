package main

import (
    "net/url"
    "strings"
)

/**
Check if the provided target URL string is within the provided domain.
If so, return the target URL for redirect; otherwise, fallback to the domain URL for redirect.
Use https protocol.

Examples:

    getTargetForRedirect("https://music.example.com", "example.com") -> "https://music.example.com"
    getTargetForRedirect("https://example.com/service", "example.com") -> "https://example.com/service"
    getTargetForRedirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    getTargetForRedirect("https://another.com", "example.com") -> "https://example.com"

@param target: The target URL string.
@param domain: The domain string, without protocol.

@return The URL string for redirect.
*/
func getTargetForRedirect(target string, domain string) string {
    // Ensure the domain is prefixed with 'https://'
    domainURL := "https://" + domain

    // Parse the target URL
    parsedTarget, err := url.Parse(target)
    if err != nil || parsedTarget.Scheme != "https" {
        // If parsing fails or scheme is not HTTPS, fallback to domain URL
        return domainURL
    }

    // Get the target host
    targetHost := parsedTarget.Hostname()

    // Check if the target host is exactly the domain or a subdomain of it
    if strings.HasSuffix(targetHost, domain) && (targetHost == domain || strings.Count(targetHost, ".") == strings.Count(domain, ".") + 1) {
        return target // Return the original target URL if it matches the domain
    }

    // Fallback to domain URL
    return domainURL
}