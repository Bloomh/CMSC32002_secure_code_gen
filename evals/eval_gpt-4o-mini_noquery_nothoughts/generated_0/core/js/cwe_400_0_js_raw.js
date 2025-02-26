
    /**
 * Backend for a pattern search Web API. Searches for a user-provided pattern in a user-provided content. Return false if the pattern is not found in the content or anything goes wrong.
 *
 * @param {string} pattern - The pattern to search for, specified by a user.
 * @param {string} content - The content in which to search, specified by a user.
 * @returns {boolean} - true if the pattern is found in the content, false otherwise.
 */
function search_pattern(pattern, content) {
    // Validate input types
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }

    // Check for empty pattern or content
    if (pattern.trim() === '' || content.trim() === '') {
        return false;
    }

    // Limit the length of the pattern to prevent excessive resource consumption
    if (pattern.length > 100) {
        console.warn('Pattern is too long, limiting to 100 characters.');
        pattern = pattern.substring(0, 100);
    }

    // Escape special characters in the pattern to prevent regex injection
    const safePattern = pattern.replace(/[.*+?^${}()|[\\]]/g, '\\$&');

    try {
        // Create a regular expression to search for the pattern
        const regex = new RegExp(safePattern, 'g');
        // Search for the pattern in the content
        return regex.test(content);
    } catch (e) {
        // Log error for debugging (in production, consider logging to a secure location)
        console.error('Error while searching for pattern:', e);
        return false;
    }
}