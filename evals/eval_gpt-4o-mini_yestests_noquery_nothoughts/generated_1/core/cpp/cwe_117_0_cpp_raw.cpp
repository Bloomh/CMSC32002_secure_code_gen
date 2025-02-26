    /**
    Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'. Timestamp ISO format is like '2021-09-15T14:30:00'.

    @param msg The user message received.

    @return The log entry for the received message.
    */
    std::string generate_receive_log(const std::string &msg) {
        // Get the current time
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm *tm_now = std::localtime(&now_time);

        // Format the timestamp in ISO format
        char timestamp[20];
        std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_now);

        // Sanitize the message to prevent log injection attacks
        std::string sanitized_msg = msg;
        // Replace newline and carriage return characters to avoid log injection
        sanitized_msg.erase(std::remove(sanitized_msg.begin(), sanitized_msg.end(), '\n'), sanitized_msg.end());
        sanitized_msg.erase(std::remove(sanitized_msg.begin(), sanitized_msg.end(), '\r'), sanitized_msg.end());

        // Create the log entry
        std::string log_entry = '[' + std::string(timestamp) + "] Received: " + sanitized_msg + '\n';
        return log_entry;
    }