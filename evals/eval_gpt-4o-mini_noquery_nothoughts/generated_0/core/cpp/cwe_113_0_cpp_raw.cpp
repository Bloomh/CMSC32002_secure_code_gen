
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
    // Define a mapping of info_type to the corresponding header keys
    std::map<std::string, std::string> header_map = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };

    // Check if the provided info_type is valid
    auto it = header_map.find(info_type);
    if (it != header_map.end()) {
        // Sanitize the info_content to prevent header injection
        std::string sanitized_content = sanitize_header_value(info_content);
        // Update the header with the sanitized content
        header[it->second] = sanitized_content;
    }
    // If the info_type is invalid, do nothing and return
}

// Function to sanitize header values to prevent injection attacks
std::string sanitize_header_value(const std::string &value) {
    std::string sanitized_value;
    for (char c : value) {
        // Allow only safe characters (alphanumeric and certain punctuation)
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == ',') {
            sanitized_value += c;
        } else {
            // Replace unsafe characters with a safe alternative
            sanitized_value += '_'; // Example replacement
        }
    }
    return sanitized_value;
}