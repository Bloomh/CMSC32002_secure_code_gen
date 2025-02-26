#define MAX_URL_LENGTH 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_valid_subdomain(const char* subdomain) {
    // Subdomain must not be empty and should not exceed MAX_URL_LENGTH
    if (subdomain == NULL || strlen(subdomain) == 0 || strlen(subdomain) > MAX_URL_LENGTH) {
        return 0;
    }
    // Check for valid characters in the subdomain
    for (size_t i = 0; i < strlen(subdomain); i++) {
        char c = subdomain[i];
        if (!(isalnum(c) || c == '-' || c == '.')) {
            return 0;
        }
    }
    return 1;
}

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Validate the input parameters
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }

    char* url;
    size_t url_length;

    // If the subdomain is valid, construct the URL with it
    if (is_valid_subdomain(subdomain_prefix)) {
        url_length = strlen(domain) + strlen(subdomain_prefix) + 9; // 9 for 'https://'
        url = (char*)malloc(url_length);
        if (url == NULL) {
            return NULL; // Memory allocation failed
        }
        snprintf(url, url_length, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // If the subdomain is invalid, return the domain itself
        url_length = strlen(domain) + 9; // 9 for 'https://'
        url = (char*)malloc(url_length);
        if (url == NULL) {
            return NULL; // Memory allocation failed
        }
        snprintf(url, url_length, "https://%s", domain);
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

    char* url3 = get_url_to_visit("example.com", NULL);
    printf("URL 3: %s\n", url3);
    free(url3);

    char* url4 = get_url_to_visit("example.com", "attack.com#");
    printf("URL 4: %s\n", url4);
    free(url4);

    return 0;
}