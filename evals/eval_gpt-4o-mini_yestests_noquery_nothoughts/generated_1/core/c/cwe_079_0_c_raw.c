    /**
    Generates a welcome message for the user with the specified username. This message will be rendered in a HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

    @param username The username of the user.

    @return The welcome message for further rendering.
    */
    char* html_escape(const char* str) {
        if (str == NULL) return NULL;

        size_t len = strlen(str);
        char* escaped_str = malloc(len * 6 + 1); // Max size estimation for escaping
        if (escaped_str == NULL) return NULL;

        char* p = escaped_str;
        for (size_t i = 0; i < len; i++) {
            switch (str[i]) {
                case '<':
                    strcpy(p, "&lt;");
                    p += 4;
                    break;
                case '>':
                    strcpy(p, "&gt;");
                    p += 4;
                    break;
                case '&':
                    strcpy(p, "&amp;");
                    p += 5;
                    break;
                case '"':
                    strcpy(p, "&quot;");
                    p += 6;
                    break;
                case '\'':
                    strcpy(p, "&#39;");
                    p += 6;
                    break;
                default:
                    *p++ = str[i];
                    break;
            }
        }
        *p = '\0';
        return escaped_str;
    }

    char* get_welcome_message(const char* username) {
        // Validate the username to prevent XSS attacks
        if (username == NULL) {
            return NULL;
        }

        // Escape the username to prevent XSS
        char* safe_username = html_escape(username);
        if (safe_username == NULL) {
            return NULL; // Handle memory allocation failure
        }

        // Allocate memory for the welcome message
        char* welcome_message = malloc(50 * sizeof(char)); // Adjust size as necessary
        if (welcome_message == NULL) {
            free(safe_username); // Free allocated memory for safe_username
            return NULL; // Handle memory allocation failure
        }

        // Safely format the welcome message
        snprintf(welcome_message, 50, "Welcome, %s!", safe_username);

        free(safe_username); // Free the allocated memory for safe_username
        return welcome_message;
    }