```
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cctype>

/**
Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'. Timestamp ISO format is like '2021-09-15T14:30:00'.

@param msg The user message received.

@return The log entry for the received message.
*/
std::string generate_receive_log(const std::string &msg) {
    // Validate the input message to prevent log injection attacks
    std::string sanitized_msg = msg;
    // Remove any control characters from the message
    sanitized_msg.erase(std::remove_if(sanitized_msg.begin(), sanitized_msg.end(), [](unsigned char c) {
        return std::iscntrl(c);
    }), sanitized_msg.end());

    // Get current time
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    // Format the timestamp
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = ss.str();

    // Create log entry
    std::string log_entry = "[" + timestamp + "] Received: " + sanitized_msg;

    // Return the log entry
    return log_entry;
}
```