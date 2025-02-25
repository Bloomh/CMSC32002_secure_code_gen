#define MAX_MSG_LEN 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.

@param msg The user message received.

@return The log entry for the received message, or NULL on error.
*/
char* generate_receive_log(const char *msg) {
    // Validate the input message length
    if (msg == NULL || strlen(msg) == 0 || strlen(msg) > MAX_MSG_LEN) {
        fprintf(stderr, "Invalid message: NULL, empty, or exceeds maximum length.\n");
        return NULL; // Invalid message, return NULL
    }

    // Get current time
    time_t now = time(NULL);
    if (now == (time_t)(-1)) {
        fprintf(stderr, "Failed to obtain the current time.\n");
        return NULL; // Error getting time
    }

    struct tm *tm_info = localtime(&now);
    if (tm_info == NULL) {
        fprintf(stderr, "Failed to convert time to local time.\n");
        return NULL; // Error converting time
    }

    // Create a timestamp in ISO format
    char timestamp[20]; // YYYY-MM-DD HH:MM:SS
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

    // Allocate memory for the log entry
    size_t log_entry_size = strlen(timestamp) + strlen(msg) + 50; // Extra space for formatting
    char *log_entry = (char *)malloc(log_entry_size);
    if (log_entry == NULL) {
        fprintf(stderr, "Memory allocation failed for log entry.\n");
        return NULL; // Memory allocation failed
    }

    // Create the log entry string
    snprintf(log_entry, log_entry_size, "[%s] Received: %s", timestamp, msg);

    return log_entry;
}

// Example usage
int main() {
    const char *user_message = "Hello, world!";
    char *log = generate_receive_log(user_message);
    if (log) {
        printf("%s\n", log);
        free(log); // Free the allocated memory
    } else {
        fprintf(stderr, "Failed to create log entry.\n");
    }
    return 0;
}