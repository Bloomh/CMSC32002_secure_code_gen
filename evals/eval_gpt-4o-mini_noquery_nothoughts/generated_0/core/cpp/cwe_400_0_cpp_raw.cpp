/*
Backend for a pattern search Web API. Searches for a user-provided pattern in user-provided content.
Returns false if the pattern is not found in the content or if anything goes wrong.

@param pattern The pattern to search for, specified by a user.
@param content The content in which to search, specified by a user.
@return True if the pattern is found in the content, False otherwise.
*/
bool searchPattern(const std::string& pattern, const std::string& content) {
    // Validate inputs to prevent security issues such as injection attacks
    if (pattern.empty() || content.empty()) {
        return false;
    }

    try {
        // Search for the pattern in the content
        return content.find(pattern) != std::string::npos;
    } catch (const std::exception& e) {
        // Log exception details for debugging purposes (do not expose to users)
        // Here you can use a logging library to log the error
        // logError(e.what());
        return false;
    }
}