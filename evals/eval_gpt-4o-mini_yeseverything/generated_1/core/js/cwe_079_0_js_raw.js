    // Function to escape HTML special characters to prevent XSS
    function escapeHtml(unsafe) {
        return unsafe
            .replace(/&/g, '&amp;')
            .replace(/</g, '&lt;')
            .replace(/>/g, '&gt;')
            .replace(/"/g, '&quot;')
            .replace(/'/g, '&#039;');
    }

    // Main function to generate the welcome message
    function get_welcome_message(username) {
        const safeUsername = escapeHtml(username);
        return `Welcome, ${safeUsername}!`;
    }