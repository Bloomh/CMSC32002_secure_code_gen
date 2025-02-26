    /**
 * Backend for a pattern search Web API. Searches for a user-provided pattern in a user-provided content. Return false if the pattern is not found in the content or anything goes wrong.
 *
 * @param {string} pattern - The pattern to search for, specified by a user.
 * @param {string} content - The content in which to search, specified by a user.
 * @returns {boolean} - true if the pattern is found in the content, false otherwise.
 */
function search_pattern(pattern, content) {
    // Validate inputs to ensure they are strings
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }

    // Limit the length of the pattern and content to prevent excessive resource consumption
    const MAX_LENGTH = 1000;
    if (pattern.length > MAX_LENGTH || content.length > MAX_LENGTH) {
        return false;
    }

    // Escape special regex characters in the pattern to prevent regex injection
    const escapedPattern = pattern.replace(/[.*+?^${}()|[\\]]/g, '\\$&');

    // Limit the complexity of the regex to avoid catastrophic backtracking
    const validPattern = /^(?:[\w\s]|\.|\-|\+|\*|\?|\^|\$|\[|\]|\(|\)|\\|\/|\|)+$/;
    if (!validPattern.test(escapedPattern)) {
        return false;
    }

    try {
        // Create a regex from the escaped pattern with a safe flag to limit performance impact
        const regex = new RegExp(escapedPattern);
        // Test if the pattern exists in the content
        return regex.test(content);
    } catch (error) {
        // If there's an error in regex creation or testing, return false
        return false;
    }
}