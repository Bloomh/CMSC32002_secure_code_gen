#define MAX_MSG_LEN 256

/**
Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.

@param msg The user message received.

@return The log entry for the received message.
*/
char* generate_receive_log(const char *msg) {
    // Check for NULL msg
    if (msg == NULL) {
        return NULL;
    }

    // Ensure the message length does not exceed the maximum length
    size_t msg_len = strlen(msg);
    if (msg_len > MAX_MSG_LEN) {
        return NULL;
    }

    // Check for newline characters to prevent log injection
    if (strchr(msg, '\n') != NULL || strchr(msg, '\r') != NULL) {
        return NULL; // Prevent log injection by rejecting messages with newlines
    }

    // Get the current time
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20]; // Buffer for timestamp
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Format the timestamp in ISO format
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", timeinfo);

    // Allocate memory for the log entry
    char *log_entry = malloc(strlen(timestamp) + strlen(msg) + 30);
    if (log_entry == NULL) {
        return NULL; // Memory allocation failed
    }

    // Create the log entry
    snprintf(log_entry, strlen(timestamp) + strlen(msg) + 30, "[%s] Received: %s", timestamp, msg);

    return log_entry;
}