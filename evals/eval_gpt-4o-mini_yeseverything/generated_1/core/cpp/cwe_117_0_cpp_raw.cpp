#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

/**
Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'. Timestamp ISO format is like '2021-09-15T14:30:00'.

@param msg The user message received.

@return The log entry for the received message.
*/
std::string generate_receive_log(const std::string &msg) {
    // Sanitize input message to prevent log injection
    std::string sanitized_msg = msg;
    size_t pos;
    // Replace newlines with a placeholder
    while ((pos = sanitized_msg.find('\n')) != std::string::npos) {
        sanitized_msg.replace(pos, 2, "[NEWLINE]");
    }
    while ((pos = sanitized_msg.find('\r')) != std::string::npos) {
        sanitized_msg.replace(pos, 2, "[CARRIAGE RETURN]");
    }

    // Get current time
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time);

    // Format timestamp in ISO format
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S");
    std::string timestamp_iso = timestamp_stream.str();

    // Create log entry
    std::string log_entry = "[" + timestamp_iso + "] Received: " + sanitized_msg;
    return log_entry;
}