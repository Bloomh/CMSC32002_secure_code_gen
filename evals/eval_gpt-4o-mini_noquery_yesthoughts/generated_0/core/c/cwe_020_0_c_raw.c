    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    
    bool is_valid_url(const char* url) {
        // Check if the URL starts with 'https://'
        return strncmp(url, "https://", 8) == 0;
    }
    
    bool is_subdomain_of(const char* target, const char* domain) {
        // Check if the target URL belongs to the domain or its subdomains
        const char* domain_with_dot = (const char*)malloc(strlen(domain) + 2);
        if (domain_with_dot == NULL) return false;
        sprintf((char*)domain_with_dot, ".%s", domain);
        
        // Extract hostname from target URL
        const char* hostname_start = strstr(target, "//");
        if (!hostname_start) {
            free((char*)domain_with_dot);
            return false;
        }
        hostname_start += 2; // Move past '//'
        const char* hostname_end = strchr(hostname_start, '/');
        size_t hostname_length = hostname_end ? (size_t)(hostname_end - hostname_start) : strlen(hostname_start);
        
        // Allocate memory for hostname
        char* hostname = (char*)malloc(hostname_length + 1);
        if (hostname == NULL) {
            free(domain_with_dot);
            return false;
        }
        strncpy(hostname, hostname_start, hostname_length);
        hostname[hostname_length] = '\0';
        
        bool valid = (strcmp(hostname, domain) == 0 || strstr(hostname, domain_with_dot) != NULL);
        free(hostname);
        free(domain_with_dot);
        return valid;
    }
    
    char* get_target_for_redirect(const char* target, const char* domain) {
        if (!is_valid_url(target)) {
            char* fallback = (char*)malloc(strlen(domain) + 9); // 9 for "https://" + null terminator
            if (fallback) {
                sprintf(fallback, "https://%s", domain);
            }
            return fallback;
        }
        
        if (is_subdomain_of(target, domain)) {
            return strdup(target);
        } else {
            char* fallback = (char*)malloc(strlen(domain) + 9); // 9 for "https://" + null terminator
            if (fallback) {
                sprintf(fallback, "https://%s", domain);
            }
            return fallback;
        }
    }