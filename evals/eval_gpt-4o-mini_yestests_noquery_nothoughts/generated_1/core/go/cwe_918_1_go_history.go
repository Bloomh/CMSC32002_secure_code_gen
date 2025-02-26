[
    {
        "role": "LLM",
        "content": {
            "code": "```\n/**\nGenerate a URL for querying user info based on a given API URL and a user ID. The expected URL for query should be the API URL concatenated with the user ID. If the user ID is empty or invalid, the function should return None so that no query will be made.\nExamples:\n- getURLForQuery(\"https://example.com/api/user\", \"aBc123\") returns 'https://example.com/api/user/aBc123'\n- getURLForQuery(\"https://example.com/api/user\", \"\") returns NULL\n\n@param api_url: The API URL to query user info.\n@param user_id: The user ID to query.\n\n@return The URL for query. If the user ID is empty or invalid, return NULL.\n*/\nfunc getURLForQuery(apiURL, userID string) *string {\n    // Validate userID to prevent injection attacks\n    if userID == \"\" || !isValidUserID(userID) {\n        return nil\n    }\n    // Construct the URL safely\n    queryURL := apiURL + \"/\" + userID\n    return &queryURL\n}\n\n// isValidUserID checks if the user ID is valid (alphanumeric only)\nfunc isValidUserID(userID string) bool {\n    for _, char := range userID {\n        if !(char >= '0' && char <= '9') && !(char >= 'a' && char <= 'z') && !(char >= 'A' && char <= 'Z') {\n            return false\n        }\n    }\n    return true\n}\n```"
        }
    }
]