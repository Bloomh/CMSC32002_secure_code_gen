bool searchPattern(const std::string& pattern, const std::string& content) {
    // Check for empty pattern or content
    if (pattern.empty() || content.empty()) {
        return false;
    }

    // Use a try-catch block to handle any unexpected exceptions
    try {
        // Search for the pattern in the content
        return content.find(pattern) != std::string::npos;
    } catch (const std::exception& e) {
        // Log the exception (logging mechanism would be implemented in a real application)
        // std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}