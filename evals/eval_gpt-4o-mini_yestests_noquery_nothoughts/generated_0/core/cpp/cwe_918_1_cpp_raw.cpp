```
#include <string>
#include <cctype>

/**
Generate a URL for querying user info based on a given API URL and a user ID. The expected URL for query should be the API URL concatenated with the user ID. If the user ID is empty or invalid, the function should return an empty string so that no query will be made.
Examples:
- get_url_for_query("https://example.com/api/user", "aBc123") returns 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") returns an empty string

@param api_url: The API URL to query user info.
@param user_id: The user ID to query.

@return The URL for query. If the user ID is empty or invalid, return an empty string.
*/
std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Check if user_id is empty or contains only whitespace
    if (user_id.empty() || std::all_of(user_id.begin(), user_id.end(), ::isspace)) {
        return "";
    }

    // Validate user_id: it should only contain alphanumeric characters
    for (char c : user_id) {
        if (!std::isalnum(c)) {
            return "";
        }
    }

    // Construct the URL
    return api_url + "/" + user_id;
}
```