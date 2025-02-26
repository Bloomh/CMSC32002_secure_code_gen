
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
    // Validate the info_type to prevent injection attacks
    if (info_type == "lang" || info_type == "encoding" || info_type == "cache") {
        // Validate info_content to ensure it does not contain malicious data
        if (!info_content.empty() && info_content.find_first_of("<>" ) == std::string::npos && info_content.length() <= 100) {
            if (info_type == "lang") {
                header["Accept-Language"] = info_content;
            } else if (info_type == "encoding") {
                header["Accept-Encoding"] = info_content;
            } else if (info_type == "cache") {
                header["Cache-Control"] = info_content;
            }
        }
    }
    // If info_type is invalid or if any validation fails, do nothing and return the original header
}