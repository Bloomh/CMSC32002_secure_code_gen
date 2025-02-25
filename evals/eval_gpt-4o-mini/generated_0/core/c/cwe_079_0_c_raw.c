#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Generates a welcome message for the user with the specified username. This message will be rendered in a HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

@param username The username of the user.

@return The welcome message for further rendering.
*/
char* escape_html(const char* str) {
    if (str == NULL) return NULL; // Handle null input
    size_t len = strlen(str);
    char* escaped = malloc(len * 6 + 1); // Allocate worst-case scenario
    if (!escaped) return NULL; // Check for malloc failure
    char* p = escaped;
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
            case '\':
                strcpy(p, "\\");
                p += 2;
                break;
            default:
                *p++ = str[i];
                break;
        }
    }
    *p = '\0';
    return escaped;
}

char* get_welcome_message(const char* username) {
    if (username == NULL) return NULL; // Handle null input
    char* safe_username = escape_html(username);
    if (!safe_username) return NULL; // Check for escape_html failure
    char* message = malloc(strlen(safe_username) + 20); // 20 for "Welcome, !"
    if (!message) {
        free(safe_username);
        return NULL; // Check for malloc failure
    }
    sprintf(message, "Welcome, %s!", safe_username);
    free(safe_username);
    return message;
}