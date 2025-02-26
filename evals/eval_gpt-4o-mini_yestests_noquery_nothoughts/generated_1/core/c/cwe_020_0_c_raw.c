    if (target == NULL || domain == NULL) {
        return NULL; // Handle null input
    }

    // Ensure the target URL starts with https
    const char* https_prefix = "https://";
    if (strncmp(target, https_prefix, strlen(https_prefix)) != 0) {
        return NULL; // Target URL must use https
    }

    // Extract the hostname from the target URL
    const char* target_hostname_start = target + strlen(https_prefix);
    const char* target_hostname_end = strchr(target_hostname_start, '/');
    if (target_hostname_end == NULL) {
        target_hostname_end = target_hostname_start + strlen(target_hostname_start);
    }

    size_t target_hostname_length = target_hostname_end - target_hostname_start;

    // Validate the target hostname against the provided domain
    // Check if the target hostname ends with the domain (to prevent subdomain attacks)
    size_t domain_length = strlen(domain);
    if (target_hostname_length >= domain_length && 
        strcmp(target_hostname_end - domain_length, domain) == 0 && 
        (target_hostname_end - domain_length > target_hostname_start) && 
        *(target_hostname_end - domain_length - 1) == '.') {
        return strdup(target); // Return the original target URL if valid
    }

    // Fallback to the domain URL
    char* fallback_url = malloc(strlen(https_prefix) + strlen(domain) + 1);
    if (fallback_url == NULL) {
        return NULL; // Handle memory allocation failure
    }
    sprintf(fallback_url, "%s%s", https_prefix, domain);
    return fallback_url;
