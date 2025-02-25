#define MAX_URL_LENGTH 256
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_valid_subdomain(const char* subdomain) {
    // Check for NULL or empty string
    if (subdomain == NULL || *subdomain == '\0') return 0;
    // Check each character in the subdomain
    for (size_t i = 0; i < strlen(subdomain); i++) {
        char c = subdomain[i];
        if (!isalnum(c) && c != '-' && c != '.') {
            return 0; // Invalid character found
        }
    }
    return 1; // Valid subdomain
}

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Validate the domain
    if (domain == NULL || strlen(domain) == 0 || strlen(domain) > MAX_URL_LENGTH) {
        return NULL; // Invalid domain
    }

    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // Memory allocation failed
    }

    // If the subdomain is valid, construct the full URL
    if (is_valid_subdomain(subdomain_prefix)) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }

    return url; // Caller is responsible for freeing the allocated memory
}