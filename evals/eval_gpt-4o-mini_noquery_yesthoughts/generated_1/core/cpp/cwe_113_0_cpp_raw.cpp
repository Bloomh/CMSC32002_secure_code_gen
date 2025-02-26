```
#include <string>
#include <map>
#include <set>

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
    // Set of valid info types
    const std::set<std::string> valid_info_types = {"lang", "encoding", "cache"};

    // Check if the info_type is valid
    if (valid_info_types.find(info_type) == valid_info_types.end()) {
        return; // Do nothing if the type is invalid
    }

    // Check for control characters in info_content
    if (info_content.find('\r') != std::string::npos || info_content.find('\n') != std::string::npos) {
        return; // Do nothing if content is invalid
    }

    // Store the information based on the type
    if (info_type == "lang") {
        header["Accept-Language"] = info_content;
    } else if (info_type == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (info_type == "cache") {
        header["Cache-Control"] = info_content;
    }
}
```