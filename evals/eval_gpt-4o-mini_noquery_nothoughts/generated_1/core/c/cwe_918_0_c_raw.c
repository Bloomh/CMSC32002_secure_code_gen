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
    // Validate the input domain
    if (domain == NULL || strlen(domain) == 0 || strlen(domain) > MAX_URL_LENGTH) {
        return NULL; // Invalid domain
    }

    // Validate the subdomain prefix
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // Return the base domain URL
        char* url = (char*)malloc(MAX_URL_LENGTH);
        if (url != NULL) {
            snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        }
        return url;
    }

    // Check for invalid characters in the subdomain
    for (int i = 0; subdomain_prefix[i] != '\0'; i++) {
        if (!isalnum(subdomain_prefix[i]) && subdomain_prefix[i] != '-' && subdomain_prefix[i] != '.') {
            return NULL; // Invalid subdomain
        }
    }

    // Ensure the subdomain does not start or end with a dot or hyphen
    if (subdomain_prefix[0] == '-' || subdomain_prefix[0] == '.' || 
        subdomain_prefix[strlen(subdomain_prefix) - 1] == '-' || 
        subdomain_prefix[strlen(subdomain_prefix) - 1] == '.') {
        return NULL; // Invalid subdomain
    }

    // Split subdomain by '.' and check for consecutive dots
    char* subdomain_copy = strdup(subdomain_prefix);
    if (subdomain_copy == NULL) {
        return NULL; // Memory allocation failed
    }
    char* token = strtok(subdomain_copy, ".");
    while (token != NULL) {
        if (strlen(token) == 0) {
            free(subdomain_copy);
            return NULL; // Invalid subdomain due to consecutive dots
        }
        token = strtok(NULL, ".");
    }
    free(subdomain_copy);

    // Construct the full URL
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url != NULL) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }
    return url;
}