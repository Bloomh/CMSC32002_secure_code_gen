```
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
    // Validate that the domain is not empty
    if domain == "" {
        return ""
    }

    // Ensure the target URL starts with https
    if !strings.HasPrefix(target, "https://") {
        return "https://" + domain
    }

    // Parse the target URL
    parsedTarget, err := url.Parse(target)
    if err != nil || parsedTarget.Scheme != "https" {
        return "https://" + domain
    }

    // Extract the host from the parsed target
    targetHost := parsedTarget.Hostname()
    allowedDomain := strings.TrimPrefix(domain, "www.")  // Handle subdomains

    // Check if the target host is within the allowed domain or matches it exactly
    if strings.HasSuffix(targetHost, allowedDomain) || targetHost == domain {
        return target
    }

    // Fallback to the domain URL
    return "https://" + domain
}
```