function getUrlForQuery(apiUrl, userId) {
    // Validate that apiUrl and userId are strings
    if (typeof apiUrl !== 'string' || typeof userId !== 'string') {
        return null;
    }

    // Trim whitespace
    apiUrl = apiUrl.trim();
    userId = userId.trim();

    // Check if userId is empty or contains invalid characters
    if (!userId || /[^a-zA-Z0-9]/.test(userId) || userId.includes('/') || userId.includes('..')) {
        return null;
    }

    // Ensure the API URL ends with a slash if necessary
    if (!apiUrl.endsWith('/')) {
        apiUrl += '/';
    }

    return apiUrl + userId;
}