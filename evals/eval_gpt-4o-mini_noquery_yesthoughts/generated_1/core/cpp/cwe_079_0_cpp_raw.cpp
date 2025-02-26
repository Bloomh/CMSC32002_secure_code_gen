```cpp
#include <string>
#include <sstream>

// Function to escape HTML special characters
std::string escape_html(const std::string &input) {
    std::ostringstream escaped;
    for (char c : input) {
        switch (c) {
            case '"': escaped << "&quot;"; break;
            case '&': escaped << "&amp;"; break;
            case '\u003c': escaped << "&lt;"; break;
            case '\u003e': escaped << "&gt;"; break;
            case '\u0027': escaped << "&#39;"; break;
            default: escaped << c;
        }
    }
    return escaped.str();
}

/*
Generates a welcome message for the user with the specified username. This message will be rendered on an HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

@param username The username of the user.
@return The welcome message for further rendering.
*/
std::string get_welcome_message(const std::string &username) {
    std::string safe_username = escape_html(username);
    return "Welcome, " + safe_username + "!";
}
```