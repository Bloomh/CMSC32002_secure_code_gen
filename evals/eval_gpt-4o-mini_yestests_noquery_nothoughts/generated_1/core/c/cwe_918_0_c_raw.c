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
    // Validate the domain
    if (domain == NULL || strlen(domain) == 0 || strlen(domain) > MAX_URL_LENGTH) {
        return NULL; // Invalid domain
    }

    // Validate the subdomain prefix
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // Return the base domain if subdomain is empty
        char* url = (char*)malloc(strlen(domain) + 9); // 9 for 'https://'
        if (url == NULL) return NULL; // Memory allocation failure
        sprintf(url, "https://%s", domain);
        return url;
    }

    // Check for invalid characters in the subdomain prefix
    for (const char* ptr = subdomain_prefix; *ptr; ptr++) {
        if (!isalnum(*ptr) && *ptr != '.' && *ptr != '-') {
            return NULL; // Invalid subdomain characters
        }
    }

    // Prevent SSRF by ensuring subdomain does not contain malicious patterns or the domain itself
    if (strstr(subdomain_prefix, "..") || strstr(subdomain_prefix, "//") ||
        strstr(subdomain_prefix, domain) != NULL ||
        strcmp(subdomain_prefix, domain) == 0) {
        return NULL; // Invalid subdomain
    }

    // Create the full URL
    size_t url_length = strlen(domain) + strlen(subdomain_prefix) + 9; // 9 for 'https://'
    if (url_length > MAX_URL_LENGTH) {
        return NULL; // URL exceeds maximum length
    }

    char* url = (char*)malloc(url_length + 1); // +1 for null terminator
    if (url == NULL) return NULL; // Memory allocation failure
    sprintf(url, "https://%s.%s", subdomain_prefix, domain);
    return url;
}