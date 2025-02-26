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
    queryURL := apiURL + "/" + userID
    return &queryURL
}

// isValidUserID checks if the user ID is valid.
func isValidUserID(userID string) bool {
    // Example validation: userID must be alphanumeric and between 1 and 20 characters long.
    match, _ := regexp.MatchString(`^[a-zA-Z0-9]{1,20}$`, userID)
    return match
}
```