// Function to generate a URL for querying user info based on a given API URL and a user ID.

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
    // Validate the API URL format
    if !isValidURL(apiURL) {
        return nil
    }
    
    // Check if userID is empty or contains invalid characters
    if userID == "" || !isValidUserID(userID) {
        return nil
    }
    
    // Construct the URL
    queryURL := apiURL + "/" + userID
    return &queryURL
}

// Helper function to validate the URL format
func isValidURL(url string) bool {
    // Check for a basic URL format validation (could be enhanced with regex)
    return strings.HasPrefix(url, "http://") || strings.HasPrefix(url, "https://")
}

// Helper function to validate the user ID
func isValidUserID(userID string) bool {
    // Check for alphanumeric characters only
    for _, char := range userID {
        if !unicode.IsLetter(char) && !unicode.IsDigit(char) {
            return false
        }
    }
    return true
}