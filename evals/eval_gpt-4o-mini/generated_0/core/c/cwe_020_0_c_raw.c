
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    // Ensure the target URL starts with https://
    if (strncmp(target, "https://", 8) != 0) {
        return strdup(domain); // Fallback to domain if not secure
    }

    // Extract the host from the target URL
    const char* start = strstr(target, "//");
    if (start == NULL) {
        return strdup(domain); // Fallback to domain if invalid URL
    }
    start += 2; // Move past the //

    const char* end = strchr(start, '/');
    size_t host_len = (end != NULL) ? (end - start) : strlen(start);

    // Check if the target host ends with the domain
    if (host_len >= strlen(domain) && 
        strncmp(start + host_len - strlen(domain), domain, strlen(domain)) == 0) {
        // Ensure the preceding character is either a dot or the start of the host
        if (host_len == strlen(domain) || start[host_len - strlen(domain) - 1] == '.') {
            return strdup(target); // Return the original target URL
        }
    }

    // If the target URL does not match the domain, return the domain URL
    return strdup(domain);
}

int main() {
    // Test cases
    printf("%s\n", get_target_for_redirect("https://music.example.com", "example.com"));
    printf("%s\n", get_target_for_redirect("https://example.com/service", "example.com"));
    printf("%s\n", get_target_for_redirect("https://blog.example.com/posts", "example.com"));
    printf("%s\n", get_target_for_redirect("https://another.com", "example.com"));
    return 0;
}
