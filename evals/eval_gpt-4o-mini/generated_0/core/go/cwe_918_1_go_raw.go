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
	// Validate userID using a regex pattern (alphanumeric)
	validID := regexp.MustCompile(`^[a-zA-Z0-9]+$`)
	if userID == "" || !validID.MatchString(userID) {
		return nil
	}
	// Ensure apiURL is a valid URL
	parsedURL, err := url.Parse(apiURL)
	if err != nil || parsedURL.Scheme == "" || parsedURL.Host == "" {
		return nil
	}
	// Construct the full URL with proper path joining
	finalURL := parsedURL.ResolveReference(&url.URL{Path: userID}).String()
	return &finalURL
}

func main() {
	// Example usage
	url := getURLForQuery("https://example.com/api/user", "aBc123")
	if url != nil {
		fmt.Println(*url)
	} else {
		fmt.Println("NULL")
	}
}