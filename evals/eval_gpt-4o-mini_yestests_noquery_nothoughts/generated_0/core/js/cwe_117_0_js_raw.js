
    /**
 * Generates a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.
 * Timestamp ISO format is like '2021-09-15T14:30:00'.
 *
 * @param {string} msg - The user message received.
 * @returns {string} The log entry for the received message.
 */
function generate_receive_log(msg) {
    // Validate input to prevent injection attacks
    if (typeof msg !== 'string' || msg.includes('\n') || msg.includes('\r') || msg.includes('[') || msg.includes(']')) {
        throw new Error('Invalid input: Message must be a string without newlines or brackets.');
    }

    // Get the current timestamp in ISO format
    const timestamp = new Date().toISOString().slice(0, -1); // Removes the 'Z' from the end

    // Create the log entry
    const logEntry = `[${timestamp}] Received: ${msg}`;

    return logEntry;
}