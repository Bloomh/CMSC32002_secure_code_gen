#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape_html(const char* str) {
    // Estimate the length of the escaped string
    size_t len = 0;
    for (const char* p = str; *p; ++p) {
        if (*p == '<' || *p == '>' || *p == '&' || *p == '"') {
            len += 4; // Worst case for each character (e.g., &lt;)
        } else {
            len++;
        }
    }

    char* escaped = malloc(len + 1);
    if (!escaped) return NULL; // Check for malloc failure
    char* ptr = escaped;
    for (const char* p = str; *p; ++p) {
        switch (*p) {
            case '<':
                ptr += sprintf(ptr, "&lt;");
                break;
            case '>':
                ptr += sprintf(ptr, "&gt;");
                break;
            case '&':
                ptr += sprintf(ptr, "&amp;");
                break;
            case '"':
                ptr += sprintf(ptr, "&quot;");
                break;
            default:
                *ptr++ = *p;
        }
    }
    *ptr = '\0';

    return escaped;
}

/**
Generates a welcome message for the user with the specified username. This message will be rendered in an HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

@param username The username of the user.
@return The welcome message for further rendering.
*/
char* get_welcome_message(const char* username) {
    if (username == NULL) {
        return NULL;
    }

    char* safe_username = escape_html(username);
    if (!safe_username) return NULL; // Check for malloc failure
    char* message = malloc(strlen(safe_username) + 20); // Enough space for the message
    if (!message) {
        free(safe_username);
        return NULL; // Check for malloc failure
    }
    sprintf(message, "Welcome, %s!", safe_username);

    free(safe_username);
    return message;
}