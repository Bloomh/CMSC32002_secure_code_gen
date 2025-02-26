
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

/**
Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'. Timestamp ISO format is like '2021-09-15T14:30:00'.

@param msg The user message received.

@return The log entry for the received message.
*/
std::string generate_receive_log(const std::string &msg) {
    // Get the current time
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);

    // Convert to ISO format
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_c), "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = oss.str();

    // Create the log entry, ensuring the message is safe from injection
    std::string safe_msg;
    for (char c : msg) {
        if (c == '\n' || c == '\r') {
            safe_msg += "[REDACTED]"; // Prevent log injection by replacing newline characters
        } else {
            safe_msg += c;
        }
    }
    std::string log_entry = "[" + timestamp + "] Received: " + safe_msg;

    return log_entry;
}