
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
    // Validate the API URL format
    try {
        const url = new URL(apiUrl);
        if (url.protocol !== 'http:' && url.protocol !== 'https:') {
            return null;
        }
    } catch (error) {
        return null;
    }
    // Validate user ID
    if (typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    // Sanitize user ID to prevent injection attacks
    const sanitizedUserId = encodeURIComponent(userId);
    // Construct and return the URL, ensuring no duplicate slashes
    return `${url.origin}${url.pathname.replace(/\/$/, '')}/${sanitizedUserId}`;
}