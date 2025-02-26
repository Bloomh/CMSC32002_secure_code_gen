#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape_html(const char* str) {
    if (str == NULL) return NULL;

    size_t len = strlen(str);
    char* escaped = malloc(len * 6 + 1); // worst case: every char is a special char
    if (escaped == NULL) return NULL; // Memory allocation failed
    char* p = escaped;

    for (const char* s = str; *s; s++) {
        switch (*s) {
            case '<':  strcpy(p, "&lt;"); p += 4; break;
            case '>':  strcpy(p, "&gt;"); p += 4; break;
            case '&':  strcpy(p, "&amp;"); p += 5; break;
            case '"': strcpy(p, "&quot;"); p += 6; break;
            case '\': strcpy(p, "&#x27;"); p += 6; break;
            default: *p++ = *s; break;
        }
    }
    *p = '\0'; // Null terminate the escaped string
    return escaped;
}

/**
Generates a welcome message for the user with the specified username. This message will be rendered in a HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

@param username The username of the user.
@return The welcome message for further rendering.
*/
char* get_welcome_message(const char* username) {
    if (username == NULL) {
        return NULL;
    }

    // Escape the username to prevent XSS
    char* safe_username = escape_html(username);
    if (safe_username == NULL) {
        return NULL; // Memory allocation failed
    }

    // Create the welcome message
    size_t message_length = strlen(safe_username) + 15; // length of "Welcome, !"
    char* message = malloc(message_length);
    if (message == NULL) {
        free(safe_username);
        return NULL; // Memory allocation failed
    }

    snprintf(message, message_length, "Welcome, %s!", safe_username);

    // Free the escaped username memory
    free(safe_username);

    return message;
}