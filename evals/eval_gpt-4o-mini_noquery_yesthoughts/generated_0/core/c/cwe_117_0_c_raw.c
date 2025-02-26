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
    if (msg == NULL) return NULL; // Ensure msg is not NULL

    // Get current time
    time_t now;
    time(&now);
    struct tm *timeinfo = localtime(&now);
    char timestamp[20]; // Buffer for ISO timestamp format
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", timeinfo);

    // Calculate the length of the message, ensuring it does not exceed MAX_MSG_LEN
    size_t msg_len = strnlen(msg, MAX_MSG_LEN); // Use strnlen for safety

    // Allocate memory for the log entry
    size_t log_len = snprintf(NULL, 0, "[%s] Received: %.*s", timestamp, (int)msg_len, msg) + 1;
    char *log_entry = malloc(log_len);
    if (log_entry == NULL) return NULL; // Handle memory allocation failure

    // Create the log entry with safe formatting
    snprintf(log_entry, log_len, "[%s] Received: %.*s", timestamp, (int)msg_len, msg);

    return log_entry;
}