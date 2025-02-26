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
        // Validate the input to prevent injection vulnerabilities
        if (info_type.empty() || info_content.empty()) {
            return; // Invalid input, return original header
        }

        std::string key;
        if (info_type == "lang") {
            key = "Accept-Language";
        } else if (info_type == "encoding") {
            key = "Accept-Encoding";
        } else if (info_type == "cache") {
            key = "Cache-Control";
        } else {
            return; // Invalid info_type, return original header
        }

        // Check for unsafe characters in the content to prevent HTTP response splitting
        if (info_content.find('\n') != std::string::npos || info_content.find('\r') != std::string::npos) {
            return; // Invalid content, return original header
        }

        // Store the content in the header map securely
        header[key] = info_content;
    }