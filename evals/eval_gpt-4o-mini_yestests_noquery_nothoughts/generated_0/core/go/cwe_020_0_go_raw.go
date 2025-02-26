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
    parsedURL, err := url.Parse(target)
    if err != nil || parsedURL.Scheme != "https" {
        return "https://" + domain
    }

    // Ensure the target URL is using the correct domain
    targetDomain := parsedURL.Hostname()
    // Check if the target domain matches the expected domain
    if targetDomain == domain || strings.HasSuffix(targetDomain, "." + domain) {
        return target
    }

    // Fallback to the domain URL
    return "https://" + domain
}