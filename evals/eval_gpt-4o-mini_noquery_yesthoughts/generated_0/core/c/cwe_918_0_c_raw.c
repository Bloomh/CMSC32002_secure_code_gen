#define MAX_URL_LENGTH 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_valid_subdomain(const char* subdomain) {
    if (subdomain == NULL) return 0; // Null check
    int len = strlen(subdomain);
    if (len == 0 || len > 63) return 0; // Valid subdomain length is between 1 and 63
    if (subdomain[0] == '-' || subdomain[len - 1] == '-') return 0; // Cannot start or end with '-'
    for (int i = 0; i < len; i++) {
        if (!(isalnum(subdomain[i]) || subdomain[i] == '-' || subdomain[i] == '.')) return 0; // Only alphanumeric, '-' and '.'
    }
    return 1;
}

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    if (domain == NULL || strlen(domain) == 0 || strlen(domain) > MAX_URL_LENGTH) {
        return NULL; // Invalid domain
    }

    // Validate the subdomain prefix
    if (!is_valid_subdomain(subdomain_prefix)) {
        return strdup(domain); // Return domain itself if subdomain is invalid
    }

    // Create the full URL
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // Memory allocation failed
    }

    // Safely create the URL string
    int written = snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    if (written < 0 || written >= MAX_URL_LENGTH) {
        free(url); // Free allocated memory on failure
        return NULL; // URL creation failed
    }

    return url;
}