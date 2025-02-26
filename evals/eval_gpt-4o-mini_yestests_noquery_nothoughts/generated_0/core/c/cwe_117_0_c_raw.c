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

    // Check for newline characters in the message to prevent log injection
    if (strchr(msg, '\n') != NULL || strchr(msg, '\r') != NULL) {
        return NULL;
    }

    char *log_entry = (char *)malloc(MAX_MSG_LEN);
    if (log_entry == NULL) {
        return NULL;
    }

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[20]; // Buffer for ISO format timestamp
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // Ensure the message length does not exceed the maximum allowed length
    snprintf(log_entry, MAX_MSG_LEN, "[%s] Received: %.240s", timestamp, msg);

    return log_entry;
}