#define MAX_MSG_LEN 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.

@param msg The user message received.

@return The log entry for the received message.
*/
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL; // Handle null input gracefully
    }

    // Ensure message length is within bounds
    size_t msg_len = strlen(msg);
    if (msg_len > MAX_MSG_LEN) {
        return NULL; // Message too long, return NULL
    }

    // Check for newlines and replace them to prevent log injection
    char sanitized_msg[MAX_MSG_LEN + 1];
    size_t sanitized_len = 0;
    for (size_t i = 0; i < msg_len && sanitized_len < MAX_MSG_LEN; i++) {
        // Replace newline characters with space
        sanitized_msg[sanitized_len++] = (msg[i] == '\n' || msg[i] == '\r') ? ' ' : msg[i];
    }
    sanitized_msg[sanitized_len] = '\0'; // Null-terminate the sanitized message

    // Get current time
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[20]; // Buffer to hold the timestamp string in ISO format
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // Allocate memory for the log entry
    size_t log_len = strlen(timestamp) + strlen(sanitized_msg) + 50; // Extra space for formatting
    char *log_entry = malloc(log_len);
    if (log_entry == NULL) {
        return NULL; // Memory allocation failed
    }

    // Create log entry
    snprintf(log_entry, log_len, "[%s] Received: %s", timestamp, sanitized_msg);

    return log_entry;
}