#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_within_domain(const char* target, const char* domain) {
    // Create a buffer to hold the domain with https
    char domain_with_https[256]; // Buffer size should be large enough to hold the domain
    snprintf(domain_with_https, sizeof(domain_with_https), "https://%s", domain);

    // Check if the target starts with the domain's HTTPS version
    return strncmp(target, domain_with_https, strlen(domain_with_https)) == 0;
}

char* get_target_for_redirect(const char* target, const char* domain) {
    // Validate inputs
    if (target == NULL || domain == NULL) {
        return NULL;
    }

    // Check if the target URL is within the provided domain
    if (is_within_domain(target, domain)) {
        // Return the target URL as it is valid
        return strdup(target);
    } else {
        // Fallback to the domain URL
        char* fallback_url = (char*)malloc(strlen(domain) + 9); // 8 for 'https://' + 1 for '\0'
        if (fallback_url == NULL) {
            return NULL; // Handle memory allocation failure
        }
        snprintf(fallback_url, strlen(domain) + 9, "https://%s", domain);
        return fallback_url;
    }
}

// Example usage
int main() {
    char* redirect_url;

    redirect_url = get_target_for_redirect("https://music.example.com", "example.com");
    printf("Redirect URL: %s\n", redirect_url);
    free(redirect_url);

    redirect_url = get_target_for_redirect("https://example.com/service", "example.com");
    printf("Redirect URL: %s\n", redirect_url);
    free(redirect_url);

    redirect_url = get_target_for_redirect("https://blog.example.com/posts", "example.com");
    printf("Redirect URL: %s\n", redirect_url);
    free(redirect_url);

    redirect_url = get_target_for_redirect("https://another.com", "example.com");
    printf("Redirect URL: %s\n", redirect_url);
    free(redirect_url);

    return 0;
}