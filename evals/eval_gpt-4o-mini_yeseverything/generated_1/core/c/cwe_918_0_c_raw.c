#define MAX_URL_LENGTH 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_valid_subdomain(const char* subdomain) {
    // Check if the subdomain is non-empty and matches the expected format
    if (subdomain == NULL || strlen(subdomain) == 0) {
        return false;
    }
    // Check for invalid characters (only allow letters, digits, and hyphens)
    for (size_t i = 0; i < strlen(subdomain); i++) {
        char c = subdomain[i];
        if (!(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9') || c == '-')) {
            return false;
        }
    }
    // Check for consecutive dots or starting/ending with a dot
    if (strstr(subdomain, "..") != NULL || subdomain[0] == '.' || subdomain[strlen(subdomain) - 1] == '.') {
        return false;
    }
    return true;
}

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    if (domain == NULL || strlen(domain) == 0) {
        return NULL; // Invalid domain
    }
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // Memory allocation failed
    }

    if (is_valid_subdomain(subdomain_prefix)) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }
    return url;
}

// Example usage
int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <domain> <subdomain_prefix>\n", argv[0]);
        return 1;
    }
    char* url = get_url_to_visit(argv[1], argv[2]);
    if (url) {
        printf("URL: %s\n", url);
        free(url);
    }
    return 0;
}