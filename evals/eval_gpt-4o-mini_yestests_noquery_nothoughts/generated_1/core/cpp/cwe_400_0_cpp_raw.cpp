/*
Backend for a pattern search Web API. Searches for a user-provided pattern in user-provided content.
Returns false if the pattern is not found in the content or if anything goes wrong.

@param pattern The pattern to search for, specified by a user.
@param content The content in which to search, specified by a user.
@return True if the pattern is found in the content, False otherwise.
*/
bool searchPattern(const std::string& pattern, const std::string& content) {
    // Check if the pattern or content is empty
    if (pattern.empty() || content.empty()) {
        return false;
    }

    try {
        // Use std::string::find to search for the pattern in the content
        return content.find(pattern) != std::string::npos;
    } catch (const std::exception& e) {
        // Log the exception message if needed (ensure to avoid logging sensitive data)
        // std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}
