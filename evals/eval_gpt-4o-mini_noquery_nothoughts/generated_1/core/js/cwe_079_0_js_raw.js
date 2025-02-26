/**
 * Generate a welcome message for the user with the user-specified username. This message will be redendered in a HTML page after the user logs in. The message will be in the format "Welcome, <username>!".
 *
 * @param {string} username - The username of the user.
 * @returns {string} The welcome message for further rendering.
 */
function get_welcome_message(username) {
    // Validate and sanitize the input to prevent XSS attacks
    const sanitizedUsername = username.replace(/</g, '&lt;').replace(/>/g, '&gt;');
    return `Welcome, ${sanitizedUsername}!`;
}