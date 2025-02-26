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
        return NULL;
    }

    size_t msg_len = strlen(msg);
    if (msg_len > MAX_MSG_LEN) {
        return NULL; // Message too long
    }

    // Allocate memory for the log entry
    size_t log_entry_size = 300;
    char *log_entry = malloc(log_entry_size); // Sufficient space for timestamp and message
    if (log_entry == NULL) {
        return NULL; // Memory allocation failed
    }

    // Get current time
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    // Format timestamp in ISO 8601 format
    char timestamp[20]; // YYYY-MM-DDTHH:MM:SS
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // Safely create log entry using snprintf to prevent buffer overflow
    int written = snprintf(log_entry, log_entry_size, "[%s] Received: %s", timestamp, msg);
    if (written < 0 || written >= log_entry_size) {
        free(log_entry); // Free memory on error
        return NULL; // Error occurred during formatting
    }

    return log_entry;
}