```
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <cctype>

// Function to sanitize header content to prevent injection attacks
std::string sanitize_header_content(const std::string &content) {
    std::string sanitized;
    for (char c : content) {
        // Allow alphanumeric and specific special characters for headers
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == ',' || c == ';') {
            sanitized += c;
        }
    }
    return sanitized;
}

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Define mapping of info_type to header keys
    std::map<std::string, std::string> info_map = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };

    // Check if the provided info_type is valid
    auto it = info_map.find(info_type);
    if (it != info_map.end()) {
        // Sanitize the info_content to prevent header injection
        std::string sanitized_content = sanitize_header_content(info_content);
        // Format the sanitized content correctly
        if (!sanitized_content.empty()) {
            // Append the new value to the existing header value if it exists
            if (header.count(it->second)) {
                header[it->second] += ", " + sanitized_content;
            } else {
                header[it->second] = sanitized_content;
            }
        }
    }
    // If the info_type is invalid, do nothing and return the original header
}
```