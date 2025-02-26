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
    // Validate the API URL
    if (typeof apiUrl !== 'string' || !apiUrl.startsWith('https://') || !apiUrl.includes('/')) {
        throw new Error('Invalid API URL');
    }
    // Validate the user ID
    if (typeof userId !== 'string' || userId.trim() === '' || userId.includes('..')) {
        return null;
    }
    // Concatenate API URL and user ID securely
    return `${apiUrl}/${encodeURIComponent(userId)}`;
}