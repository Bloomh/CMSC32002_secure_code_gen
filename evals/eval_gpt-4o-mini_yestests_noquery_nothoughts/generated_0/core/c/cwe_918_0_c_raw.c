#define MAX_URL_LENGTH 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    // Validate domain
    if (domain == NULL || strlen(domain) == 0 || strlen(domain) > MAX_URL_LENGTH) {
        return NULL;
    }

    // Validate subdomain_prefix
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // Return the domain URL if subdomain is empty
        char* url = (char*)malloc(strlen(domain) + 8); // 8 for 'https://'
        if (url == NULL) return NULL;
        sprintf(url, "https://%s", domain);
        return url;
    }

    // Check for invalid characters in subdomain_prefix
    for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
        if (!isalnum(subdomain_prefix[i]) && subdomain_prefix[i] != '.' && subdomain_prefix[i] != '-') {
            // Invalid character found
            char* url = (char*)malloc(strlen(domain) + 8); // 8 for 'https://'
            if (url == NULL) return NULL;
            sprintf(url, "https://%s", domain);
            return url;
        }
    }

    // Construct the URL
    char* url = (char*)malloc(strlen(domain) + strlen(subdomain_prefix) + 9); // 9 for 'https://'
    if (url == NULL) return NULL;
    sprintf(url, "https://%s.%s", subdomain_prefix, domain);
    return url;
}