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
    // Ensure the domain starts with 'https://'
    domainURL := "https://" + domain

    // Parse the target URL
    parsedTarget, err := url.Parse(target)
    if err != nil || parsedTarget.Scheme != "https" {
        return domainURL
    }

    // Normalize the domain to lower case for comparison
    domainLower := strings.ToLower(domain)
    targetHost := strings.ToLower(parsedTarget.Hostname())

    // Check if the target host matches the provided domain or its subdomains
    if strings.HasSuffix(targetHost, domainLower) && (targetHost == domainLower || strings.HasPrefix(targetHost, domainLower + ".")) {
        return target
    }

    // Fallback to the domain URL
    return domainURL
}