#include <map>
#include <string>
#include <iostream>
#include <regex>

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
    // Create a mapping of valid info types to their corresponding header keys
    std::map<std::string, std::string> valid_types = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };

    // Check if the provided info_type is valid
    auto it = valid_types.find(info_type);
    if (it != valid_types.end()) {
        // Sanitize the info_content to prevent injection attacks
        std::string sanitized_content = std::regex_replace(info_content, std::regex("[\r\n]+"), ""); // Remove newlines
        sanitized_content = std::regex_replace(sanitized_content, std::regex("[^\x20-\x7E]+"), ""); // Remove non-printable characters

        // Update the header with the new information
        header[it->second] = sanitized_content;
    }
    // If the info_type is invalid, do nothing and return the original header
}

// Example usage
int main() {
    std::map<std::string, std::string> response_header;
    store_info_in_header("lang", "en-US", response_header);
    store_info_in_header("encoding", "gzip", response_header);
    store_info_in_header("invalid_type", "value", response_header); // This should not change the header

    // Print the updated header
    for (const auto &pair : response_header) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    return 0;
}