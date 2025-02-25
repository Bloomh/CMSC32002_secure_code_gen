    /**
 * Generates a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.
 * Timestamp ISO format is like '2021-09-15T14:30:00'.
 *
 * @param {string} msg - The user message received.
 * @returns {string} The log entry for the received message.
 */
function generate_receive_log(msg) {
    // Helper function to get current timestamp in ISO format
    function getCurrentTimestamp() {
        return new Date().toISOString();
    }

    // Helper function to sanitize the message
    function sanitizeMessage(msg) {
        // Escape special characters to prevent log injection
        return msg.replace(/\/g, '\\\\')
                  .replace(/'/g, '\\u0027')
                  .replace(/"/g, '\\u0022')
                  .replace(/\n/g, '\\n') // Prevent newlines in logs
                  .replace(/\r/g, '\\r'); // Prevent carriage returns in logs
    }

    // Validate that msg is a string
    if (typeof msg !== 'string') {
        throw new Error('Invalid input: msg must be a string.');
    }

    // Sanitize the input message to prevent log injection
    const sanitizedMsg = sanitizeMessage(msg);
    const timestamp = getCurrentTimestamp();
    return `[${timestamp}] Received: ${sanitizedMsg}`;
}