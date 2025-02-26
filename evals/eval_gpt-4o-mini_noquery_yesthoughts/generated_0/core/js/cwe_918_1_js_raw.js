function getUrlForQuery(apiUrl, userId) {
    // Validate inputs
    if (typeof apiUrl !== 'string' || typeof userId !== 'string') { return null; }
    
    // Regular expression to validate the API URL
    const urlPattern = /^(https?:\/\/)?([\w-]+\.)+[\w-]+(\/\S*)?$/;
    // Validate the userId to allow only alphanumeric characters
    const userIdPattern = /^[a-zA-Z0-9]+$/;
    
    // Check if the API URL and user ID are valid
    if (!urlPattern.test(apiUrl) || !userIdPattern.test(userId)) { return null; }
    
    // Return the concatenated URL
    return `${apiUrl}/${userId}`;
}