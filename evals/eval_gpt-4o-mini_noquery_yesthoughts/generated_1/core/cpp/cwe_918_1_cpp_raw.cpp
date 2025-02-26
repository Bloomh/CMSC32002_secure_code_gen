```
#include <string>
#include <regex>

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
    // Validate the user ID using a regex pattern (alphanumeric characters only)
    std::regex user_id_pattern("^[a-zA-Z0-9]+$");
    if (user_id.empty() || !std::regex_match(user_id, user_id_pattern)) {
        return ""; // Return empty string for invalid user ID
    }
    // Ensure the API URL ends with a '/' for proper concatenation
    std::string valid_api_url = api_url;
    if (!valid_api_url.empty() && valid_api_url.back() != '/') {
        valid_api_url += '/';
    }
    // Construct and return the full URL
    return valid_api_url + user_id;
}
```