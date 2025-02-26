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
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // Normalize info_type to lower case for case insensitive comparison
    std::string normalized_type = info_type;
    std::transform(normalized_type.begin(), normalized_type.end(), normalized_type.begin(), ::tolower);

    // Validate info_content to prevent header injection
    if (info_content.find('\n') != std::string::npos || info_content.find('\r') != std::string::npos) {
        // Invalid content, do not modify the header
        return;
    }

    // Store the information based on the info_type
    if (normalized_type == "lang") {
        header["Accept-Language"] = info_content;
    } else if (normalized_type == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (normalized_type == "cache") {
        header["Cache-Control"] = info_content;
    } else {
        // Invalid info_type, do not modify the header
        return;
    }
}
```