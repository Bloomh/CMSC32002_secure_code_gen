    char* escape_html(const char* str) {
        // Allocate enough space for the escaped string
        size_t len = strlen(str);
        char* escaped = malloc(len * 6 + 1); // Worst-case scenario for escaping
        if (!escaped) {
            return NULL; // Handle memory allocation failure
        }
        char* ptr = escaped;
        for (const char* s = str; *s; s++) {
            switch (*s) {
                case '<':
                    strcpy(ptr, "&lt;");
                    ptr += 4;
                    break;
                case '>':
                    strcpy(ptr, "&gt;");
                    ptr += 4;
                    break;
                case '&':
                    strcpy(ptr, "&amp;");
                    ptr += 5;
                    break;
                case '"':
                    strcpy(ptr, "&quot;");
                    ptr += 6;
                    break;
                case '\'':
                    strcpy(ptr, "&#39;");
                    ptr += 5;
                    break;
                default:
                    *ptr++ = *s;
                    break;
            }
        }
        *ptr = '\0';
        return escaped;
    }

    char* get_welcome_message(const char* username) {
        if (username == NULL) {
            return NULL; // Handle null username
        }
        char* safe_username = escape_html(username);
        if (!safe_username) {
            return NULL; // Handle memory allocation failure
        }
        // Allocate memory for the welcome message
        char* message = malloc(strlen(safe_username) + 15); // 15 = length of "Welcome, !"
        if (!message) {
            free(safe_username); // Free the escaped username
            return NULL; // Handle memory allocation failure
        }
        sprintf(message, "Welcome, %s!", safe_username);
        free(safe_username); // Free the escaped username
        return message;
    }