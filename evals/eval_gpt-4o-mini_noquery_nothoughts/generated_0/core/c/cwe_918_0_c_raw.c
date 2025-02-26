#define MAX_URL_LENGTH 256

/**
Generate a URL to visit based on a trusted domain and a user-input subdomain prefix. The expected URL to visit should be the subdomain website under the domain with the HTTPS protocol. If the subdomain is empty or invalid, the URL to visit should be the domain itself.
Examples:
- get_url_to_visit('example.com', 'subdomain') returns 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') returns 'https://a.b.example.com'

@param domain: The trusted domain.
@param subdomain: The user-input subdomain to visit.

@return: The URL to visit.
*/
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Check if domain is valid
    if (domain == NULL || strlen(domain) == 0 || strlen(domain) > MAX_URL_LENGTH) {
        return NULL;
    }

    // Check if subdomain_prefix is valid
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0 || strlen(subdomain_prefix) > MAX_URL_LENGTH) {
        // Return the domain as is if subdomain is invalid
        char* url = (char*)malloc(strlen(domain) + 8); // 8 for 'https://' and '\0'
        if (url == NULL) return NULL; // Check for malloc failure
        sprintf(url, "https://%s", domain);
        return url;
    }

    // Validate subdomain_prefix for invalid characters (only allow alphanumeric and periods)
    for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
        if (!(isalnum(subdomain_prefix[i]) || subdomain_prefix[i] == '.')) {
            // Return the domain as is if subdomain contains invalid characters
            char* url = (char*)malloc(strlen(domain) + 8);
            if (url == NULL) return NULL; // Check for malloc failure
            sprintf(url, "https://%s", domain);
            return url;
        }
    }

    // Create the full URL
    char* url = (char*)malloc(strlen(domain) + strlen(subdomain_prefix) + 9); // 9 for 'https://.' and '\0'
    if (url == NULL) return NULL; // Check for malloc failure
    sprintf(url, "https://%s.%s", subdomain_prefix, domain);
    return url;
}