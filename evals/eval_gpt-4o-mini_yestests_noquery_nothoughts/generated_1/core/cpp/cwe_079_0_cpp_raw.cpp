/*
Generates a welcome message for the user with the specified username. This message will be rendered on an HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

@param username The username of the user.
@return The welcome message for further rendering.
*/
#include <string>
#include <algorithm>
#include <iostream>

std::string get_welcome_message(const std::string &username) {
    // Sanitize the username to prevent XSS attacks
    std::string safe_username = username;
    // Replace <, >, &, ', " with their HTML entity equivalents
    std::string::size_type pos;
    const std::pair<std::string, std::string> replacements[] = {
        {"<", "&lt;"},
        {">", "&gt;"},
        {"&", "&amp;"},
        {"\"", "&quot;"},
        {"'", "&#39;"}
    };

    for (const auto &replacement : replacements) {
        while ((pos = safe_username.find(replacement.first)) != std::string::npos) {
            safe_username.replace(pos, replacement.first.length(), replacement.second);
        }
    }

    return "Welcome, " + safe_username + "!";
}