```cpp
#include <map>
#include <string>
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
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Validate info_content to prevent injection attacks
    if (info_content.empty() || info_content.find_first_of("<>\"'\n\r") != std::string::npos) {
        return; // Invalid content, return without making changes
    }

    // Transform info_type to lowercase for case-insensitive comparison
    std::string type_lower = info_type;
    std::transform(type_lower.begin(), type_lower.end(), type_lower.begin(), ::tolower);

    // Store the content based on the type
    if (type_lower == "lang") {
        header["Accept-Language"] = info_content;
    } else if (type_lower == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (type_lower == "cache") {
        header["Cache-Control"] = info_content;
    }
    // If the type is invalid, do nothing and return the original header
}
```