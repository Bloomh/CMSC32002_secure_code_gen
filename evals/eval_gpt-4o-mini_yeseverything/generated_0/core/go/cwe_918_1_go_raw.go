package main

import (
    "fmt"
    "net/url"
    "regexp"
)

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
    // Construct the URL safely
    parsedURL, err := url.Parse(apiURL)
    if err != nil {
        return nil
    }
    // Add the user ID to the path
    parsedURL.Path += "/" + userID
    result := parsedURL.String()
    return &result
}

// isValidUserID validates the user ID format.
func isValidUserID(userID string) bool {
    // User ID must be alphanumeric and between 1 to 30 characters
    if len(userID) < 1 || len(userID) > 30 {
        return false
    }
    // Use a regex to ensure the user ID does not contain invalid characters
    re := regexp.MustCompile(`^[a-zA-Z0-9]+$`)
    return re.MatchString(userID)
}

func main() {
    // Example usage
    url := getURLForQuery("https://example.com/api/user", "aBc123")
    if url != nil {
        fmt.Println(*url)
    } else {
        fmt.Println("NULL")
    }

    // Test with an empty user ID
    url = getURLForQuery("https://example.com/api/user", "")
    if url != nil {
        fmt.Println(*url)
    } else {
        fmt.Println("NULL")
    }

    // Test with an invalid user ID
    url = getURLForQuery("https://example.com/api/user", "../clear")
    if url != nil {
        fmt.Println(*url)
    } else {
        fmt.Println("NULL")
    }
}