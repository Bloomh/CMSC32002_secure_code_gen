
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
    if (typeof apiUrl !== 'string' || !/^https?:\/\/.test(apiUrl)) {
        throw new Error('Invalid API URL');
    }
    // Validate the user ID
    if (typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }

    // Sanitize the user ID
    const sanitizedUserId = encodeURIComponent(userId);
    // Construct the URL for querying user info
    const finalUrl = new URL(sanitizedUserId, apiUrl);
    // Ensure the constructed URL is valid and starts with the provided API URL
    if (!finalUrl.href.startsWith(apiUrl)) {
        throw new Error('Constructed URL is not valid');
    }
    return finalUrl.href;
}