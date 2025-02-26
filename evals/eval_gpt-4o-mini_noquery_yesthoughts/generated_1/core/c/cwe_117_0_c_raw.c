#define MAX_MSG_LEN 256
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.

@param msg The user message received.

@return The log entry for the received message, or NULL if an error occurs.
*/
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL; // Handle null input
    }

    // Get current time
    time_t now;
    time(&now);
    struct tm *tm_info;
    char timestamp[20]; // YYYY-MM-DDTHH:MM:SS
    tm_info = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // Prepare log entry
    size_t msg_len = strlen(msg);
    if (msg_len > MAX_MSG_LEN) {
        msg_len = MAX_MSG_LEN; // Truncate message length
    }

    // Allocate memory for log entry
    size_t log_size = strlen(timestamp) + msg_len + 30; // Extra space for formatting and null terminator
    char *log_entry = malloc(log_size);
    if (log_entry == NULL) {
        return NULL; // Memory allocation failed
    }

    // Format the log entry securely
    snprintf(log_entry, log_size, "[%s] Received: %.*s", timestamp, (int)msg_len, msg);

    return log_entry; // Caller is responsible for freeing the memory
}