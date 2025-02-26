    /**
Generates a welcome message for the user with the specified username. This message will be rendered in a HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

@param username The username of the user.

@return The welcome message for further rendering.
*/
char* get_welcome_message(const char* username) {
    // Check for NULL username
    if (username == NULL) {
        return NULL;
    }

    // Escape the username to prevent XSS attacks
    char* escaped_username = escape_html(username);
    if (escaped_username == NULL) {
        return NULL; // Memory allocation failed
    }

    // Prepare the welcome message template
    const char* welcome_template = "Welcome, %s!";
    int length = snprintf(NULL, 0, welcome_template, escaped_username);

    // Allocate memory for the final welcome message
    char* welcome_message = (char*)malloc(length + 1);
    if (welcome_message == NULL) {
        free(escaped_username);
        return NULL; // Memory allocation failed
    }

    // Safely format the welcome message with escaped username
    snprintf(welcome_message, length + 1, welcome_template, escaped_username);

    // Clean up
    free(escaped_username);

    return welcome_message;
}

char* escape_html(const char* str) {
    if (str == NULL) return NULL;
    size_t len = strlen(str);
    char* escaped = (char*)malloc(len * 6 + 1); // Worst case: every character needs to be escaped
    if (!escaped) return NULL;
    char* p = escaped;
    for (size_t i = 0; i < len; i++) {
        switch (str[i]) {
            case '&': p += sprintf(p, "&amp;"); break;
            case '<': p += sprintf(p, "&lt;"); break;
            case '>': p += sprintf(p, "&gt;"); break;
            case '"': p += sprintf(p, "&quot;"); break;
            case '\': p += sprintf(p, "&#39;"); break;
            default: *p++ = str[i];
        }
    }
    *p = '\0';
    return escaped;
}