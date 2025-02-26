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
    // Ensure the target URL uses HTTPS
    if !strings.HasPrefix(target, "https://") {
        return "https://" + domain
    }

    // Parse the target URL
    parsedURL, err := url.Parse(target)
    if err != nil {
        return "https://" + domain // Fallback in case of error
    }

    // Validate the host of the parsed URL
    targetHost := parsedURL.Hostname()
    domainParts := strings.Split(domain, ".")

    // Check if the host of the parsed URL matches the provided domain or is a valid subdomain
    if strings.HasSuffix(targetHost, domain) {
        return target // Safe to redirect to the target URL
    }

    // Check for potential subdomain attacks
    if len(domainParts) > 1 {
        // Ensure the last two parts of the host match the domain
        hostParts := strings.Split(targetHost, ".")
        if len(hostParts) >= 2 && hostParts[len(hostParts)-2] == domainParts[len(domainParts)-2] {
            return target // Subdomain is valid
        }
    }

    // Fallback to the domain URL
    return "https://" + domain
}
```