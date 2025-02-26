
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    
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
        // Ensure input is not NULL
        if (target == NULL || domain == NULL) {
            return NULL;
        }
        
        // Check if the target starts with https://
        if (strncmp(target, "https://", 8) != 0) {
            return NULL;
        }
        
        // Create a buffer for the domain with https:// prefix
        char domain_with_https[256];
        snprintf(domain_with_https, sizeof(domain_with_https), "https://%s", domain);
        
        // Parse the target URL to extract the hostname
        char* url_copy = strdup(target);
        if (url_copy == NULL) {
            return NULL; // Handle strdup failure
        }
        char* target_host = strtok(url_copy + 8, "/"); // Skip https://
        
        // Check if the target URL's host matches the domain
        if (target_host != NULL) {
            // Ensure the domain is a complete match, not a substring
            if (strcmp(target_host, domain) == 0 || 
                (strstr(target_host, domain) != NULL && strstr(target_host, ".") != NULL)) {
                free(url_copy);
                return strdup(target);
            }
        }
        free(url_copy);
        // Fallback to the domain URL
        return strdup(domain_with_https);
    }
