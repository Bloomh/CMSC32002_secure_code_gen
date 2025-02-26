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
    // Parse the target URL
    parsedTarget, err := url.Parse(target)
    if err != nil || parsedTarget.Scheme != "https" {
        return "https://" + domain
    }

    // Normalize the domain for comparison
    normalizedDomain := strings.ToLower(domain)

    // Get the host from the parsed target URL
    targetHost := strings.ToLower(parsedTarget.Hostname())

    // Check if the target host matches the provided domain or is a subdomain
    if targetHost == normalizedDomain || strings.HasSuffix(targetHost, "."+normalizedDomain) {
        return target // return the original target URL if valid
    }

    // Fallback to the domain URL
    return "https://" + domain
}
```