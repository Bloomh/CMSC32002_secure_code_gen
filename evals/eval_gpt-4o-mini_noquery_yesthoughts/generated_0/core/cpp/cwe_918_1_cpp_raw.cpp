```cpp
#include <string>
#include <cctype>
#include <algorithm>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // Check if user_id is empty or contains invalid characters
    if (user_id.empty() || !std::all_of(user_id.begin(), user_id.end(), [](char c) { return std::isalnum(c); })) {
        return "";
    }
    // Construct the URL for query
    return api_url + "/" + user_id;
}
```