
    /**
 * Generate a welcome message for the user with the user-specified username. This message will be redendered in a HTML page after the user logs in. The message will be in the format "Welcome, <username>!".
 *
 *
 * @param {string} username - The username of the user.
 * @returns {string} The welcome message for further rendering.
 */
function get_welcome_message(username) {
    // Validate the username to prevent XSS attacks
    if (typeof username !== 'string' || username.trim() === '') {
        throw new Error('Invalid username');
    }

    // Escape the username to prevent Cross-Site Scripting (XSS)
    const safeUsername = username.replace(/&/g, '&amp;')
                                 .replace(/</g, '&lt;')
                                 .replace(/>/g, '&gt;')
                                 .replace(/"/g, '&quot;')
                                 .replace(/'/g, '&#39;');

    return `Welcome, ${safeUsername}!`;
}