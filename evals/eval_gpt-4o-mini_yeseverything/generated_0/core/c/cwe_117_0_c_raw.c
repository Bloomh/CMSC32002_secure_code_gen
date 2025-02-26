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
    // Validate input
    if (msg == NULL) {
        return NULL;
    }

    // Ensure msg length does not exceed MAX_MSG_LEN
    size_t msg_len = strlen(msg);
    if (msg_len > MAX_MSG_LEN) {
        msg_len = MAX_MSG_LEN;
    }

    // Allocate memory for log entry
    char *log_entry = malloc(256 + msg_len);
    if (log_entry == NULL) {
        return NULL; // Handle memory allocation failure
    }

    // Get current time
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[20]; // Format YYYY-MM-DD HH:MM:SS
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

    // Sanitize msg to prevent log injection by replacing newlines with a space
    char sanitized_msg[MAX_MSG_LEN + 1];
    size_t sanitized_len = 0;
    for (size_t i = 0; i < msg_len && sanitized_len < MAX_MSG_LEN; ++i) {
        if (msg[i] == '\n') { // Correctly checking for newline character
            sanitized_msg[sanitized_len++] = ' ';
        } else if (msg[i] == '\r') { // Handle carriage return as well
            continue; // Skip carriage return
        } else {
            sanitized_msg[sanitized_len++] = msg[i];
        }
    }
    sanitized_msg[sanitized_len] = '\0'; // Null-terminate the sanitized message

    // Create log entry
    snprintf(log_entry, 256 + sanitized_len, "[%s] Received: %s", timestamp, sanitized_msg);

    return log_entry;
}