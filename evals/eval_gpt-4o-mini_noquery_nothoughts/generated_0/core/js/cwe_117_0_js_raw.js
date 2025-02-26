/**
 * Generates a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.
 * Timestamp ISO format is like '2021-09-15T14:30:00'.
 *
 * @param {string} msg - The user message received.
 * @returns {string} The log entry for the received message.
 */
function generate_receive_log(msg) {
    // Validate input to ensure it's a non-empty string
    if (typeof msg !== 'string' || msg.trim() === '') {
        throw new Error('Invalid message: message must be a non-empty string.');
    }
    // Sanitize the message to prevent injection attacks
    const sanitizedMsg = msg.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
    // Get current timestamp in ISO format
    const timestamp = new Date().toISOString();
    // Create log entry
    return `[${timestamp}] Received: ${sanitizedMsg}`;
}