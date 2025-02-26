    /**
 * Generates a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.
 * Timestamp ISO format is like '2021-09-15T14:30:00'.
 *
 * @param {string} msg - The user message received.
 * @returns {string} The log entry for the received message.
 */
function generate_receive_log(msg) {
    // Validate input to prevent log injection attacks
    if (typeof msg !== 'string') {
        throw new Error('Invalid message format');
    }

    // Sanitize the message to remove any potentially harmful characters
    const sanitizedMsg = msg.replace(/[^a-zA-Z0-9\s.,!?]/g, '');

    // Get the current timestamp in ISO format
    const timestamp = new Date().toISOString(); // Retain the 'Z' to indicate UTC

    // Create the log entry
    return `[${timestamp}] Received: ${sanitizedMsg}`;
}