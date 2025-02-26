```
/**
Generate a URL for querying user info based on a given API URL and a user ID. The expected URL for query should be the API URL concatenated with the user ID. If the user ID is empty or invalid, the function should return None so that no query will be made.
Examples:
- getURLForQuery("https://example.com/api/user", "aBc123") returns 'https://example.com/api/user/aBc123'
- getURLForQuery("https://example.com/api/user", "") returns NULL

@param api_url: The API URL to query user info.
@param user_id: The user ID to query.

@return The URL for query. If the user ID is empty or invalid, return NULL.
*/
func getURLForQuery(apiURL, userID string) *string {
    if userID == "" || !isValidUserID(userID) {
        return nil
    }
    // Ensure the API URL ends with a slash
    if apiURL[len(apiURL)-1] != '/' {
        apiURL += "/"
    }
    fullURL := apiURL + userID
    return &fullURL
}

// Helper function to validate user ID
func isValidUserID(userID string) bool {
    // Add validation logic, e.g., checking for alphanumeric characters
    for _, char := range userID {
        if !(('a' <= char && char <= 'z') || ('A' <= char && char <= 'Z') || ('0' <= char && char <= '9')) {
            return false
        }
    }
    return true
}
```