    std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
        // Check if user_id is empty or contains invalid characters
        if (user_id.empty() || user_id.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != std::string::npos) {
            return ""; // Return empty string for invalid user IDs
        }

        // Construct the URL for the query
        return api_url + "/" + user_id;
    }