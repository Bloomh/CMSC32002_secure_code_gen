
    /**
 * Backend for a pattern search Web API. Searches for a user-provided pattern in a user-provided content. Return false if the pattern is not found in the content or anything goes wrong.
 *
 * @param {string} pattern - The pattern to search for, specified by a user.
 * @param {string} content - The content in which to search, specified by a user.
 * @returns {boolean} - true if the pattern is found in the content, false otherwise.
 */
function search_pattern(pattern, content) {
    // Validate inputs to prevent injection attacks
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }
    
    // Escape special characters in the pattern to prevent regex injection
    const escapedPattern = pattern.replace(/[-/\^$.*+?()[\]{}|]/g, '\\$&');
    const regex = new RegExp(escapedPattern);
    
    try {
        // Check if the pattern exists in the content
        return regex.test(content);
    } catch (error) {
        // Handle any errors that may occur during regex execution
        console.error('An error occurred while searching for the pattern:', error);
        return false;
    }
}