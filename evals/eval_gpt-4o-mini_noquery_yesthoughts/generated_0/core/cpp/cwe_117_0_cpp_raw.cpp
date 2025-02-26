```
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <algorithm>

/**
Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'. Timestamp ISO format is like '2021-09-15T14:30:00'.

@param msg The user message received.

@return The log entry for the received message.
*/
std::string generate_receive_log(const std::string &msg) {
    // Get current time
    std::time_t now = std::time(nullptr);
    std::tm *tm_now = std::localtime(&now);

    // Create a string stream to format the timestamp
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(tm_now, "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = timestamp_stream.str();

    // Sanitize the message to prevent log injection
    std::string sanitized_msg = msg;
    // Replace newlines and carriage returns with spaces
    sanitized_msg.erase(std::remove(sanitized_msg.begin(), sanitized_msg.end(), '\n'), sanitized_msg.end());
    sanitized_msg.erase(std::remove(sanitized_msg.begin(), sanitized_msg.end(), '\r'), sanitized_msg.end());
    // Optionally handle other special characters, e.g., escaping quotes
    sanitized_msg.erase(std::remove(sanitized_msg.begin(), sanitized_msg.end(), '"'), sanitized_msg.end());

    // Create the log entry
    std::ostringstream log_entry;
    log_entry << '[' << timestamp << '] ' << "Received: " << sanitized_msg;

    return log_entry.str();
}
```