/*
Generates a welcome message for the user with the specified username. This message will be rendered on an HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

@param username The username of the user.
@return The welcome message for further rendering.
*/
std::string get_welcome_message(const std::string &username) {
    // Sanitize the username to prevent XSS attacks
    std::string safe_username = username;
    // Replace special HTML characters with their corresponding HTML entities
    std::string::size_type pos;
    const std::string html_entities[5][2] = {
        {"&", "&amp;"},
        {"<", "&lt;"},
        {">", "&gt;"},
        {"\"", "&quot;"},
        {"'", "&#39;"}
    };
    for (const auto &entity : html_entities) {
        while ((pos = safe_username.find(entity[0])) != std::string::npos) {
            safe_username.replace(pos, entity[0].length(), entity[1]);
        }
    }
    return "Welcome, " + safe_username + "!";
}