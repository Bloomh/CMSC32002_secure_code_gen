char* encode_html(const char* str) {
    size_t len = strlen(str);
    char* encoded = malloc(len * 6 + 1); // worst-case scenario: every char is encoded
    char* p = encoded;
    for (size_t i = 0; i < len; i++) {
        switch (str[i]) {
            case '<':
                p += sprintf(p, "&lt;");
                break;
            case '>':
                p += sprintf(p, "&gt;");
                break;
            case '&':
                p += sprintf(p, "&amp;");
                break;
            case '"':
                p += sprintf(p, "&quot;");
                break;
            case '\'':
                p += sprintf(p, "&#39;");
                break;
            default:
                *p++ = str[i];
        }
    }
    *p = '\0';
    return encoded;
}

char* get_welcome_message(const char* username) {
    // Sanitize the username to prevent XSS
    char* safe_username = encode_html(username);
    // Allocate memory for the welcome message
    char* message = malloc(strlen(safe_username) + 15); // "Welcome, " + "!"
    sprintf(message, "Welcome, %s!", safe_username);
    free(safe_username);
    return message;
}