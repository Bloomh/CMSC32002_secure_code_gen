    /**
    Generates a welcome message for the user with the specified username. This message will be rendered in a HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

    @param username The username of the user.

    @return The welcome message for further rendering.
    */
    char* get_welcome_message(const char* username) {
        // Validate username to prevent XSS
        if (username == NULL || strlen(username) == 0) {
            return NULL;
        }

        // Allocate memory for the welcome message
        char* welcome_message = (char*)malloc(256 * sizeof(char));
        if (welcome_message == NULL) {
            return NULL; // Memory allocation failed
        }

        // Allocate memory for the safe username
        char* safe_username = (char*)malloc(strlen(username) * 6 + 1); // Worst-case scenario for escaping
        if (safe_username == NULL) {
            free(welcome_message);
            return NULL; // Memory allocation failed
        }

        char* p = safe_username;
        for (const char* s = username; *s; s++) {
            switch (*s) {
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
                case '\':
                    strcpy(p, "\\");
                    p += 2;
                    break;
                default:
                    *p++ = *s;
            }
        }
        *p = '\0'; // Null terminate the safe_username

        // Create the welcome message
        snprintf(welcome_message, 256, "Welcome, %s!", safe_username);

        free(safe_username); // Free the allocated memory for the safe username
        return welcome_message;
    }

    // Example usage:
    // char* message = get_welcome_message("<script>alert('XSS')</script>");
    // printf("%s\n", message);
    // free(message);