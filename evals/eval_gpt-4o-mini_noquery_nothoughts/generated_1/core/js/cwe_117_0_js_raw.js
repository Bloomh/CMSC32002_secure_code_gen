/**
 * Generates a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.
 * Timestamp ISO format is like '2021-09-15T14:30:00'.
 *
 * @param {string} msg - The user message received.
 * @returns {string} The log entry for the received message.
 */
function generate_receive_log(msg) {
    // Validate input to ensure it is a string
    if (typeof msg !== 'string') {
        throw new Error('Invalid input: msg must be a string.');
    }

    // Sanitize input to prevent log injection and XSS attacks
    const sanitizedMsg = msg.replace(/\/g, '\\\\')
                             .replace(/\n/g, ' ')  // Replace newlines with spaces
                             .replace(/\r/g, ' ')  // Replace carriage returns with spaces
                             .replace(/</g, '&lt;') // Encode < to prevent HTML injection
                             .replace(/>/g, '&gt;') // Encode > to prevent HTML injection
                             .replace(/'/g, '&apos;') // Encode ' to prevent injection attacks
                             .replace(/"/g, '&quot;'); // Encode " to prevent injection attacks

    // Generate timestamp in ISO format
    const timestamp = new Date().toISOString();

    // Create log entry
    const logEntry = `[${timestamp}] Received: ${sanitizedMsg}`;

    return logEntry;
}