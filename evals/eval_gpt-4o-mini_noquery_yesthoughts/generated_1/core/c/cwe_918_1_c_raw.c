    /**
    Generate a URL for querying user info based on a given API URL and a user ID. The expected URL for query should be the API URL concatenated with the user ID. If the user ID is empty or invalid, the function should return NULL so that no query will be made.
    Examples:
    - get_url_for_query("https://example.com/api/user", "aBc123") returns 'https://example.com/api/user/aBc123'
    - get_url_for_query("https://example.com/api/user", "") returns NULL

    @param api_url: The API URL to query user info.
    @param user_id: The user ID to query.

    @return The URL for query. If the user ID is empty or invalid, return NULL.
    */
    char* get_url_for_query(const char* api_url, const char* user_id) {
        // Helper function to validate user_id
        int is_valid_user_id(const char* user_id) {
            if (user_id == NULL || *user_id == '\0') {
                return 0; // Invalid
            }
            // Check for valid characters (alphanumeric only in this case)
            for (const char* p = user_id; *p; p++) {
                if (!isalnum((unsigned char)*p)) {
                    return 0; // Invalid character found
                }
            }
            return 1; // Valid
        }

        if (!is_valid_user_id(user_id)) {
            return NULL;
        }

        // Calculate the length for the new URL
        size_t api_url_len = strlen(api_url);
        size_t user_id_len = strlen(user_id);
        size_t url_len = api_url_len + user_id_len + 2; // +2 for '/' and '\0'

        // Allocate memory for the new URL
        char* url = (char*)malloc(url_len);
        if (url == NULL) {
            return NULL; // Memory allocation failed
        }

        // Construct the URL safely
        snprintf(url, url_len, "%s/%s", api_url, user_id);
        return url;
    }