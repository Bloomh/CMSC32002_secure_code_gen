    /**
 * Generates a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.
 * Timestamp ISO format is like '2021-09-15T14:30:00'.
 *
 * @param {string} msg - The user message received.
 * @returns {string} The log entry for the received message.
 */
function generate_receive_log(msg) {
    if (typeof msg !== 'string' || msg === null || msg === undefined || msg.trim() === '') {
        throw new Error('Invalid message: must be a non-empty string.');
    }

    const escapeLogMessage = (message) => {
        return message
            .replace(/[\n\r]/g, ' ') // Replace newlines and carriage returns with a space
            .replace(/\/g, '\\') // Escape backslashes
            .replace(/'/g, '\\' + "'") // Escape single quotes
            .replace(/"/g, '\\' + '"') // Escape double quotes
            .replace(/</g, '&lt;') // Escape less than
            .replace(/>/g, '&gt;'); // Escape greater than
    };

    const timestamp = new Date().toISOString();
    const sanitizedMsg = escapeLogMessage(msg);
    return `[${timestamp}] Received: ${sanitizedMsg}`;
}