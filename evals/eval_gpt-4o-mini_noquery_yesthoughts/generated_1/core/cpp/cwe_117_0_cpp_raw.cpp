```
#include <string>
#include <chrono>
#include <ctime>
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
    // Get current time
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time);

    // Format the timestamp in ISO format
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = oss.str();

    // Sanitize the message to prevent log injection
    std::string sanitized_msg;
    for (char c : msg) {
        // Escape brackets
        if (c == '[') {
            sanitized_msg += "\[";
        } else if (c == ']') {
            sanitized_msg += "\]";
        } else if (std::iscntrl(c) || c == '\\' || c == '"') {
            // Escape backslashes and quotes
            sanitized_msg += "\\" + std::string(1, c);
        } else {
            sanitized_msg += c;
        }
    }

    // Create the log entry
    return "[" + timestamp + "] Received: " + sanitized_msg;
}
```