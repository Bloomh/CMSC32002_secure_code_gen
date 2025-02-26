```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    // Check if api_url or user_id is NULL or user_id is empty
    if (api_url == NULL || user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // Validate user_id: it should contain only alphanumeric characters
    for (size_t i = 0; i < strlen(user_id); i++) {
        if (!isalnum((unsigned char)user_id[i])) {
            return NULL;
        }
    }

    // Calculate the length of the new URL
    size_t url_length = strlen(api_url) + strlen(user_id) + 2; // +2 for '/' and '\0'
    char* url = (char*)malloc(url_length);
    if (url == NULL) {
        return NULL; // Memory allocation failed
    }

    // Construct the URL safely
    snprintf(url, url_length, "%s/%s", api_url, user_id);

    return url;
}

int main() {
    char* url = get_url_for_query("https://example.com/api/user", "aBc123");
    if (url != NULL) {
        printf("Generated URL: %s\n", url);
        free(url);
    } else {
        printf("Invalid user ID or URL\n");
    }
    return 0;
}
```