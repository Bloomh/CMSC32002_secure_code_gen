
/**
 * Generates a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.
 * Timestamp ISO format is like '2021-09-15T14:30:00'.
 *
 * @param {string} msg - The user message received.
 * @returns {string} The log entry for the received message.
 */
function generate_receive_log(msg) {
    // Validate and sanitize the input message
    if (typeof msg !== 'string') {
        throw new Error('Invalid message type');
    }
    // Sanitize to remove potential XSS characters and newlines
    const sanitizedMsg = msg.replace(/[<>\n\r]/g, '');

    // Get the current timestamp in ISO format without 'Z'
    const timestamp = new Date().toISOString().slice(0, 19);

    // Format the log entry
    return `[${timestamp}] Received: ${sanitizedMsg}`;
}