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
    // Validate input message to prevent buffer overflow
    if (msg == NULL || strlen(msg) >= MAX_MSG_LEN) {
        return NULL; // or handle error appropriately
    }

    // Get current time
    time_t now;
    time(&now);
    struct tm *tm_info = localtime(&now);

    // Allocate memory for the log entry with additional space for the timestamp and null terminator
    char *log_entry = malloc(MAX_MSG_LEN + 50); // extra space for timestamp
    if (log_entry == NULL) {
        return NULL; // Memory allocation failed
    }

    // Format timestamp
    char timestamp[30];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // Create log entry safely, ensuring no buffer overflow occurs
    snprintf(log_entry, MAX_MSG_LEN + 50, "[%s] Received: %.255s", timestamp, msg);

    return log_entry;
}