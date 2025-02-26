[
    {
        "role": "LLM",
        "content": {
            "code": "    std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {\n        // Check if user_id is empty or contains invalid characters\n        if (user_id.empty() || user_id.find_first_not_of(\"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_\") != std::string::npos) {\n            return \"\"; // Return empty string for invalid user IDs\n        }\n\n        // Construct the URL for the query\n        return api_url + \"/\" + user_id;\n    }"
        }
    }
]