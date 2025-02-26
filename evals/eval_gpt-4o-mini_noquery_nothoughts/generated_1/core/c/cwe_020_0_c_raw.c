
    /**
Check if the provided target URL string is within the provided domain.
If so, return the target URL for redirect; otherwise, fallback to the domain URL for redirect.
Use https protocol.

Examples:
    get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
    get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
    get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

@param target: The target URL string.
@param domain: The domain string, without protocol.

@return The URL string for redirect.
*/
char* get_target_for_redirect(const char* target, const char* domain) {
    // Ensure the target URL and domain are not NULL
    if (target == NULL || domain == NULL) {
        return NULL;
    }

    // Check if the target starts with https://
    if (strncmp(target, "https://", 8) != 0) {
        return NULL; // Only allow HTTPS URLs
    }

    // Create a buffer to hold the domain URL
    size_t domain_len = strlen(domain);
    char* domain_url = malloc(domain_len + 9); // 8 for https:// + 1 for null terminator
    if (domain_url == NULL) {
        return NULL; // Handle memory allocation failure
    }
    snprintf(domain_url, domain_len + 9, "https://%s", domain);

    // Check if the target URL is from the same domain
    const char* domain_start = strstr(target, domain);
    if (domain_start != NULL) {
        // Ensure the domain is at the correct position
        if ((domain_start == target + 8 && (domain_start[domain_len] == '/' || domain_start[domain_len] == '\0')) || 
            (domain_start == target + 8 + domain_len && *(domain_start - 1) == '/')) {
            char* result = strdup(target); // Copy the target URL if valid
            free(domain_url);
            return result;
        }
    }

    // Fallback to the domain URL
    free(domain_url);
    return domain_url; // Return the constructed domain URL
}