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
    // Validate input
    if (target == NULL || domain == NULL) {
        return NULL;
    }

    // Check if the target URL starts with 'https://'
    if (strncmp(target, "https://", 8) != 0) {
        return strdup(domain); // Fallback to domain if not HTTPS
    }

    // Extract the host from the target URL
    const char* start = target + 8; // Skip 'https://'
    const char* end = strchr(start, '/');
    size_t host_length = (end != NULL) ? (end - start) : strlen(start);

    // Allocate memory for the host string
    char* host = (char*)malloc(host_length + 1);
    if (host == NULL) {
        return NULL; // Memory allocation failure
    }
    strncpy(host, start, host_length);
    host[host_length] = '\0'; // Null-terminate the string

    // Check if the host matches the domain
    int is_valid = (strcmp(host, domain) == 0 || strstr(host, domain) != NULL);
    free(host);

    // Return appropriate URL
    return is_valid ? strdup(target) : strdup(domain);
}

// Example usage
int main() {
    char* redirect1 = get_target_for_redirect("https://music.example.com", "example.com");
    printf("Redirect 1: %s\n", redirect1);
    free(redirect1);

    char* redirect2 = get_target_for_redirect("https://example.com/service", "example.com");
    printf("Redirect 2: %s\n", redirect2);
    free(redirect2);

    char* redirect3 = get_target_for_redirect("https://blog.example.com/posts", "example.com");
    printf("Redirect 3: %s\n", redirect3);
    free(redirect3);

    char* redirect4 = get_target_for_redirect("https://another.com", "example.com");
    printf("Redirect 4: %s\n", redirect4);
    free(redirect4);

    return 0;
}