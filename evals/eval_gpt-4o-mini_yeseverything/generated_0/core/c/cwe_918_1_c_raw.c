#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    // Validate input parameters
    if (api_url == NULL || user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // Check for directory traversal attempts
    if (strstr(user_id, "../") != NULL) {
        return NULL;
    }

    // Calculate the length of the new URL
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t new_url_len = api_url_len + user_id_len + 2; // +2 for '/' and null terminator

    // Allocate memory for the new URL
    char* new_url = (char*)malloc(new_url_len);
    if (new_url == NULL) {
        return NULL; // Memory allocation failed
    }

    // Construct the new URL
    snprintf(new_url, new_url_len, "%s/%s", api_url, user_id);

    return new_url;
}

// Example usage
int main() {
    char* url = get_url_for_query("https://example.com/api/user", "aBc123");
    if (url) {
        printf("Generated URL: %s\n", url);
        free(url); // Free allocated memory
    } else {
        printf("No valid URL generated.\n");
    }
    return 0;
}