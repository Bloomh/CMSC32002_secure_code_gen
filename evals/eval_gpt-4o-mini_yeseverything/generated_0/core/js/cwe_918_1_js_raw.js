function getUrlForQuery(apiUrl, userId) {
    // Validate the API URL and user ID
    if (!apiUrl || typeof apiUrl !== 'string' || !userId || typeof userId !== 'string' || userId.includes('../')) {
        return null;
    }
    // Create a new URL object to help construct the final URL
    try {
        const url = new URL(apiUrl);
        // Append the user ID to the pathname safely
        url.pathname += '/' + encodeURIComponent(userId);
        return url.toString();
    } catch (error) {
        return null; // Return null if the URL construction fails
    }
}