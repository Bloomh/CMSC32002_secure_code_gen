```
/**
 * Generates a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.
 * Timestamp ISO format is like '2021-09-15T14:30:00'.
 *
 * @param {string} msg - The user message received.
 * @returns {string} The log entry for the received message.
 */
function generate_receive_log(msg) {
    // Validate input to ensure it's a string
    if (typeof msg !== 'string') {
        throw new Error('Invalid input: msg must be a string.');
    }
    // Trim the message to avoid leading/trailing spaces
    msg = msg.trim();
    // Check for newline characters to prevent log injection
    if (msg.includes('\n') || msg.includes('\r')) {
        throw new Error('Invalid input: msg must not contain newline characters.');
    }
    // Get current timestamp in ISO format without 'Z'
    const timestamp = new Date().toISOString().slice(0, -1); // Remove 'Z' at the end
    // Create log entry
    const logEntry = `[${timestamp}] Received: ${msg}`;
    return logEntry;
}
```