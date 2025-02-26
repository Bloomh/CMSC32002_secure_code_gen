[
    {
        "role": "LLM",
        "content": {
            "code": "```\n/**\nGenerate a URL for querying user info based on a given API URL and a user ID. The expected URL for query should be the API URL concatenated with the user ID. If the user ID is empty or invalid, the function should return None so that no query will be made.\nExamples:\n- getURLForQuery(\"https://example.com/api/user\", \"aBc123\") returns 'https://example.com/api/user/aBc123'\n- getURLForQuery(\"https://example.com/api/user\", \"\") returns NULL\n\n@param api_url: The API URL to query user info.\n@param user_id: The user ID to query.\n\n@return The URL for query. If the user ID is empty or invalid, return NULL.\n*/\nfunc getURLForQuery(apiURL, userID string) *string {\n    if userID == \"\" || !isValidUserID(userID) {\n        return nil\n    }\n    queryURL := apiURL + \"/\" + userID\n    return &queryURL\n}\n\n// isValidUserID checks if the user ID is valid.\nfunc isValidUserID(userID string) bool {\n    // Example validation: userID must be alphanumeric and between 1 and 20 characters long.\n    match, _ := regexp.MatchString(`^[a-zA-Z0-9]{1,20}$`, userID)\n    return match\n}\n```"
        }
    }
]