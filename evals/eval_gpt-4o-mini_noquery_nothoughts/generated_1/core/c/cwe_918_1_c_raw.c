
    /**
Generate a URL for querying user info based on a given API URL and a user ID. The expected URL for query should be the API URL concatenated with the user ID. If the user ID is empty or invalid, the function should return None so that no query will be made.
Examples:
- get_url_for_query("https://example.com/api/user", "aBc123") returns 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") returns NULL

@param api_url: The API URL to query user info.
@param user_id: The user ID to query.

@return The URL for query. If the user ID is empty or invalid, return NULL.
*/
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Validate the API URL
    if (api_url == NULL || strlen(api_url) == 0) {
        return NULL;
    }

    // Validate the user ID
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // Ensure the user ID is safe for inclusion in the URL
    for (size_t i = 0; i < strlen(user_id); i++) {
        if (!isalnum(user_id[i]) && user_id[i] != '-') {
            return NULL; // Invalid character in user ID
        }
    }

    // Allocate memory for the new URL
    size_t url_length = strlen(api_url) + strlen(user_id) + 2; // +2 for '/' and null terminator
    char* full_url = (char*)malloc(url_length);
    if (full_url == NULL) {
        return NULL; // Memory allocation failed
    }

    // Construct the full URL safely
    snprintf(full_url, url_length, "%s/%s", api_url, user_id);

    return full_url;
}