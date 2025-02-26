```cpp
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <algorithm>

/**
Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'. Timestamp ISO format is like '2021-09-15T14:30:00'.

@param msg The user message received.

@return The log entry for the received message.
*/
std::string generate_receive_log(const std::string &msg) {
    // Get current time
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    // Format the timestamp as ISO 8601
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = oss.str();

    // Sanitize the message to prevent log injection attacks
    std::string sanitized_msg = msg;
    // Replace newline characters with spaces
    sanitized_msg.erase(std::remove(sanitized_msg.begin(), sanitized_msg.end(), '\n'), sanitized_msg.end());
    sanitized_msg.erase(std::remove(sanitized_msg.begin(), sanitized_msg.end(), '\r'), sanitized_msg.end());

    // Escape any brackets or special characters that may affect log parsing
    sanitized_msg = std::regex_replace(sanitized_msg, std::regex("[\[\]]"), "");

    // Create the log entry
    std::string log_entry = '[' + timestamp + "] Received: " + sanitized_msg;
    return log_entry;
}
```