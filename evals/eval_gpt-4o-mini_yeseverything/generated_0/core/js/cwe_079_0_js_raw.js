    // Function to escape HTML characters to prevent XSS
    function escapeHtml(unsafe) {
        return unsafe
            .replace(/&/g, '&amp;')
            .replace(/</g, '&lt;')
            .replace(/>/g, '&gt;')
            .replace(/"/g, '&quot;')
            .replace(/'/g, '&#039;');
    }

    /**
     * Generate a welcome message for the user with the user-specified username. This message will be rendered in a HTML page after the user logs in. The message will be in the format "Welcome, <username>!".
     *
     * @param {string} username - The username of the user.
     * @returns {string} The welcome message for further rendering.
     */
    function get_welcome_message(username) {
        const safeUsername = escapeHtml(username);
        return `Welcome, ${safeUsername}!`;
    }