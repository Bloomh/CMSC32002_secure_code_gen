/*
Generates a welcome message for the user with the specified username. This message will be rendered on an HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

@param username The username of the user.
@return The welcome message for further rendering.
*/
std::string get_welcome_message(const std::string &username) {
    // Sanitize the username to prevent XSS attacks
    std::string safe_username;
    for (char c : username) {
        // Escape HTML special characters
        switch (c) {
            case '<': safe_username += "&lt;"; break;
            case '>': safe_username += "&gt;"; break;
            case '&': safe_username += "&amp;"; break;
            case '"': safe_username += "&quot;"; break;
            case '\\': safe_username += "&#x27;"; break;
            default: safe_username += c;
        }
    }
    return "Welcome, " + safe_username + "!";
}