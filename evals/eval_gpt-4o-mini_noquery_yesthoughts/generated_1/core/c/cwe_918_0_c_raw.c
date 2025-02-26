#define MAX_URL_LENGTH 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_valid_subdomain(const char* subdomain) {
    if (subdomain == NULL || strlen(subdomain) == 0) {
        return 0; // Invalid if NULL or empty
    }
    // Check length (accounting for the HTTPS protocol and domain)
    if (strlen(subdomain) > MAX_URL_LENGTH - strlen("https://") - strlen(".") - 1) {
        return 0; // Invalid if too long
    }
    // Check for valid characters (letters, digits, hyphens)
    for (size_t i = 0; i < strlen(subdomain); i++) {
        if (!isalnum(subdomain[i]) && subdomain[i] != '-') {
            return 0; // Invalid character found
        }
    }
    return 1; // Valid subdomain
}

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    if (domain == NULL || strlen(domain) == 0) {
        return NULL; // Invalid domain
    }
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // Memory allocation failure
    }

    if (is_valid_subdomain(subdomain_prefix)) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }

    return url;
}

// Example usage
int main() {
    char* url1 = get_url_to_visit("example.com", "subdomain");
    printf("URL 1: %s\n", url1);
    free(url1);

    char* url2 = get_url_to_visit("example.com", "a.b");
    printf("URL 2: %s\n", url2);
    free(url2);

    char* url3 = get_url_to_visit(NULL, "subdomain");
    if (url3 == NULL) {
        printf("Invalid domain provided.\n");
    }

    char* url4 = get_url_to_visit("example.com", NULL);
    if (url4 != NULL) {
        printf("URL 4: %s\n", url4);
        free(url4);
    } else {
        printf("Invalid subdomain provided.\n");
    }

    return 0;
}