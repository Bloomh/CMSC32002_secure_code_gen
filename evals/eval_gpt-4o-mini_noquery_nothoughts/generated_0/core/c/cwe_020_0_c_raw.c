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
    // Validate input parameters
    if (target == NULL || domain == NULL) {
        return NULL; // Invalid input
    }

    // Check if the target URL starts with the correct protocol
    if (strncmp(target, "https://", 8) != 0) {
        return NULL; // Invalid protocol
    }

    // Allocate memory for the domain URL with the https protocol
    size_t domain_length = strlen(domain);
    char* domain_with_protocol = (char*)malloc(domain_length + 9); // 8 for https:// and 1 for null terminator
    if (domain_with_protocol == NULL) {
        return NULL; // Memory allocation failure
    }
    snprintf(domain_with_protocol, domain_length + 9, "https://%s", domain);

    // Check if the target URL starts with the domain URL
    if (strncmp(target, domain_with_protocol, strlen(domain_with_protocol)) == 0) {
        free(domain_with_protocol);
        return strdup(target); // Return the target URL if it matches
    }

    free(domain_with_protocol);
    // If not, return the domain URL
    char* result = strdup(domain_with_protocol); // Return the domain URL for redirect
    return result;
}