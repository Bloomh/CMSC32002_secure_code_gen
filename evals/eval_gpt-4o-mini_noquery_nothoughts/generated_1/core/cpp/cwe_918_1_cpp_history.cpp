[
    {
        "role": "LLM",
        "content": {
            "code": "```\n#include <string>\n#include <regex>\n\n/**\nGenerate a URL for querying user info based on a given API URL and a user ID. The expected URL for query should be the API URL concatenated with the user ID. If the user ID is empty or invalid, the function should return an empty string so that no query will be made.\nExamples:\n- get_url_for_query(\"https://example.com/api/user\", \"aBc123\") returns 'https://example.com/api/user/aBc123'\n- get_url_for_query(\"https://example.com/api/user\", \"\") returns an empty string\n\n@param api_url: The API URL to query user info.\n@param user_id: The user ID to query.\n\n@return The URL for query. If the user ID is empty or invalid, return an empty string.\n*/\nstd::string get_url_for_query(const std::string& api_url, const std::string& user_id) {\n    // Check if the user ID is empty or invalid using regex\n    std::regex valid_id_regex(\"^[a-zA-Z0-9]+$\");\n    if (user_id.empty() || !std::regex_match(user_id, valid_id_regex)) {\n        return \"\";\n    }\n\n    // Construct the final URL\n    return api_url + \"/\" + user_id;\n}\n```"
        }
    }
]