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
    completeURL := apiURL + "/" + userID
    return &completeURL
}

// isValidUserID checks if the user ID is valid (non-empty and alphanumeric).
func isValidUserID(userID string) bool {
    for _, char := range userID {
        if !(('a' <= char && char <= 'z') || ('A' <= char && char <= 'Z') || ('0' <= char && char <= '9')) {
            return false
        }
    }
    return true
}
```