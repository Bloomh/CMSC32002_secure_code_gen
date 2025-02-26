```
#include <string>
#include <map>
#include <algorithm>
#include <cctype>

/**
Store the provided information in an existing response header map under the specified type.
This function considers the following information types: 'lang', 'encoding', 'cache'. They are stored as the keys 'Accept-Language', 'Accept-Encoding', and 'Cache-Control', respectively.
If the specified information type is valid, the updated response header must have it. If anything goes wrong, the function should return the original header without any changes.

@param info_type The type of information to store in the header.
@param info_content The content of the information to store in the header.
@param header The existing response header map.

@return The updated response header map with the stored information.
*/
std::string sanitize_content(const std::string &content) {
    std::string sanitized;
    for (char c : content) {
        // Allow only safe characters (alphanumeric and some special characters)
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == ',') {
            sanitized += c;
        }
    }
    return sanitized;
}

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Define valid types and corresponding header keys
    const std::map<std::string, std::string> valid_types = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };

    // Check if the info_type is valid
    auto it = valid_types.find(info_type);
    if (it != valid_types.end()) {
        // Sanitize the info_content to prevent injection
        std::string sanitized_content = sanitize_content(info_content);
        // Update the header with the sanitized content
        header[it->second] = sanitized_content;
    }
    // If info_type is invalid, do nothing (original header remains unchanged)
}
```