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
    // Validate the user ID
    if userID == "" || !isValidUserID(userID) {
        return nil
    }
    // Construct the URL
    queryURL := apiURL + "/" + userID
    return &queryURL
}

// isValidUserID checks if the user ID follows a specific pattern or rules
func isValidUserID(userID string) bool {
    // Here we can implement specific validation rules, for example:
    // Check if the userID is alphanumeric and within a certain length
    if len(userID) < 1 || len(userID) > 20 {
        return false
    }
    for _, char := range userID {
        if !isAlphanumeric(char) {
            return false
        }
    }
    return true
}

// isAlphanumeric checks if a character is alphanumeric
func isAlphanumeric(c rune) bool {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
}
```