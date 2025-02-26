```
/**
 * Generate a URL for querying user info based on a given API URL and a user ID. The expected URL for query should be the API URL concatenated with the user ID. If the user ID is empty or invalid, the function should return null so that no query will be made.
 * Examples:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') returns 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') returns null
 *
 * @param {string} apiUrl - The API URL to query user info.
 * @param {string} userId - The user ID to query.
 * @returns {string|null} - The URL for query.
 */
function getUrlForQuery(apiUrl, userId) {
    // Validate the apiUrl
    try {
        new URL(apiUrl);
    } catch (e) {
        return null; // Invalid URL
    }

    // Validate userId: must be non-empty and alphanumeric
    if (!userId || !/^[a-zA-Z0-9]+$/.test(userId)) {
        return null;
    }

    // Construct and return the full URL
    return `${apiUrl}/${userId}`;
}
```