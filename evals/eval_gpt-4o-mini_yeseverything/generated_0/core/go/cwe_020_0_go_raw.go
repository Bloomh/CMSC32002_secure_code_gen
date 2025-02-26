package main

import (
    "fmt"
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
    // Parse the target URL
    parsedTarget, err := url.Parse(target)
    if err != nil || parsedTarget.Scheme != "https" {
        return "https://" + domain
    }

    // Check if the host of the target URL ends with the domain
    if strings.HasSuffix(parsedTarget.Hostname(), domain) {
        return target
    }

    // Fallback to the domain URL
    return "https://" + domain
}

func main() {
    // Example usage
    fmt.Println(getTargetForRedirect("https://music.example.com", "example.com")) // Output: https://music.example.com
    fmt.Println(getTargetForRedirect("https://example.com/service", "example.com")) // Output: https://example.com/service
    fmt.Println(getTargetForRedirect("https://blog.example.com/posts", "example.com")) // Output: https://blog.example.com/posts
    fmt.Println(getTargetForRedirect("https://another.com", "example.com")) // Output: https://example.com
    fmt.Println(getTargetForRedirect("http://insecure.com", "example.com")) // Output: https://example.com
    fmt.Println(getTargetForRedirect("https://malicious.com", "example.com")) // Output: https://example.com
}