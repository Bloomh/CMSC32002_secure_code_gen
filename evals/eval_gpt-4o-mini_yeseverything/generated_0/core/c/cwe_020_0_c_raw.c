#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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
    // Check if target or domain is NULL
    if (target == NULL || domain == NULL) {
        return NULL;
    }

    // Construct the expected domain URL with HTTPS
    char expected_domain[256];
    snprintf(expected_domain, sizeof(expected_domain), "https://%s", domain);

    // Check if the target URL starts with the expected domain URL
    if (strncmp(target, expected_domain, strlen(expected_domain)) == 0) {
        // Target is within the domain
        char* redirect_url = (char*)malloc(strlen(target) + 1);
        if (redirect_url == NULL) {
            return NULL;  // Memory allocation failed
        }
        strcpy(redirect_url, target);
        return redirect_url;
    } else {
        // Fallback to the domain URL
        char* fallback_url = (char*)malloc(strlen(expected_domain) + 1);
        if (fallback_url == NULL) {
            return NULL;  // Memory allocation failed
        }
        strcpy(fallback_url, expected_domain);
        return fallback_url;
    }
}

// Example usage
int main() {
    char* redirect = get_target_for_redirect("https://music.example.com", "example.com");
    printf("Redirect URL: %s\n", redirect);
    free(redirect);
    redirect = get_target_for_redirect("https://another.com", "example.com");
    printf("Redirect URL: %s\n", redirect);
    free(redirect);
    return 0;
}