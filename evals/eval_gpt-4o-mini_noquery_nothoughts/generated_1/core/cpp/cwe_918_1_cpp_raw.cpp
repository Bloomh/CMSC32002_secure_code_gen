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
    // Check if the user ID is empty or invalid using regex
    std::regex valid_id_regex("^[a-zA-Z0-9]+$");
    if (user_id.empty() || !std::regex_match(user_id, valid_id_regex)) {
        return "";
    }

    // Construct the final URL
    return api_url + "/" + user_id;
}
```