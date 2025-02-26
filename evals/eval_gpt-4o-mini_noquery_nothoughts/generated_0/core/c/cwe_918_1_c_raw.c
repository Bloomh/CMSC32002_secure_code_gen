
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Check for null or empty user_id
    if (api_url == NULL || user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // Validate user_id to ensure it contains only allowed characters (e.g., alphanumeric)
    for (const char *p = user_id; *p; p++) {
        if (!isalnum((unsigned char)*p)) {
            return NULL;
        }
    }

    // Calculate the length for the new URL
    size_t url_length = strlen(api_url) + strlen(user_id) + 2; // +2 for '/' and '\0'
    char *full_url = (char *)malloc(url_length);

    if (full_url == NULL) {
        return NULL; // Memory allocation failed
    }

    // Construct the full URL safely
    snprintf(full_url, url_length, "%s/%s", api_url, user_id);

    return full_url;
}