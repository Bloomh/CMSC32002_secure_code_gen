    std::string escape_html(const std::string &input) {
        std::string output;
        for (char c : input) {
            switch (c) {
                case '&': output += "&amp;"; break;
                case '"': output += "&quot;"; break;
                case '\u003c': output += "&lt;"; break;
                case '\u003e': output += "&gt;"; break;
                default: output += c; break;
            }
        }
        return output;
    }

    std::string get_welcome_message(const std::string &username) {
        std::string safe_username = escape_html(username);
        return "Welcome, " + safe_username + "!";
    }