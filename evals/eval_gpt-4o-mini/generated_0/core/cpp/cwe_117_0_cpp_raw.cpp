std::string generate_receive_log(const std::string &msg) {
    // Get the current time
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // Convert to ISO format
    std::tm *tm_now = std::gmtime(&now_time);
    char timestamp[20]; // Buffer for ISO format timestamp
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_now);

    // Sanitize the message to prevent log injection
    std::string sanitized_msg;
    for (char c : msg) {
        if (c == '\n' || c == '\r') {
            sanitized_msg += ' '; // Replace newlines with space
        } else {
            sanitized_msg += c;
        }
    }

    // Generate the log entry
    return std::string("[") + timestamp + "] Received: " + sanitized_msg;
}