#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <iostream>

/**
Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'. Timestamp ISO format is like '2021-09-15T14:30:00'.

@param msg The user message received.

@return The log entry for the received message.
*/
std::string generate_receive_log(const std::string &msg) {
    // Get current time
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);

    // Convert to ISO format
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_time_t), "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = oss.str();

    // Sanitize message to prevent log injection
    std::string sanitized_msg = msg;
    sanitized_msg.erase(std::remove(sanitized_msg.begin(), sanitized_msg.end(), '\n'), sanitized_msg.end());
    sanitized_msg.erase(std::remove(sanitized_msg.begin(), sanitized_msg.end(), '\r'), sanitized_msg.end());

    // Generate log entry
    std::string log_entry = '[' + timestamp + "] Received: " + sanitized_msg;
    return log_entry;
}

int main(int argc, char *argv[]) {
    // Example usage
    std::string message = "Hello, World!";
    std::string log = generate_receive_log(message);
    std::cout << log << std::endl;
    return 0;
}