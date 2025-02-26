    /**
    Generates a welcome message for the user with the specified username. This message will be rendered in an HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

    @param username The username of the user.

    @return The welcome message for further rendering.
    */
    char* get_welcome_message(const char* username) {
        // Check for NULL username to prevent NULL dereference
        if (username == NULL) {
            return NULL;
        }

        // Allocate memory for the welcome message
        char* message = (char*)malloc(50 * sizeof(char));
        if (message == NULL) {
            return NULL; // Handle memory allocation failure
        }

        // Escape the username to prevent XSS
        char* escaped_username = html_escape(username);
        if (escaped_username == NULL) {
            free(message);
            return NULL; // Handle memory allocation failure in escape function
        }

        // Safely format the welcome message
        snprintf(message, 50, "Welcome, %s!", escaped_username);

        // Free the allocated memory for escaped_username
        free(escaped_username);

        // Return the safely constructed message
        return message;
    }

    char* html_escape(const char* str) {
        if (str == NULL) return NULL;
        size_t len = strlen(str);
        char* escaped = (char*)malloc(len * 6 + 1); // Worst case for HTML escaping
        if (escaped == NULL) return NULL; // Handle memory allocation failure
        char* p = escaped;
        for (const char* s = str; *s; s++) {
            switch (*s) {
                case '<':
                    strcpy(p, "&lt;"); p += 4; break;
                case '>':
                    strcpy(p, "&gt;"); p += 4; break;
                case '&':
                    strcpy(p, "&amp;"); p += 5; break;
                case '"':
                    strcpy(p, "&quot;"); p += 6; break;
                case '\':
                    strcpy(p, "&#x27;"); p += 6; break;
                default:
                    *p++ = *s;
            }
        }
        *p = '\0';
        return escaped;
    }