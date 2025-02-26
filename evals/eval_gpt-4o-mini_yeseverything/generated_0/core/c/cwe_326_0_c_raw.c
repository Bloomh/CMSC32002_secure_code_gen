#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Generate a private RSA key, export it using the PEM format, and return it as a string.
 * Execute the command "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" to generate the key.
 *
 * @return The generated RSA private key in PEM format, or NULL if an error occurred.
 */
char *create_private_key() {
    const int key_length = 2048; // Minimum secure RSA key length
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d", key_length);

    // Open a pipe to the command
    FILE *fp;
    char *buffer = NULL;
    size_t size = 0;

    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Error executing command
    }

    // Read the output from the command
    ssize_t read;
    size_t total_read = 0;
    size_t buffer_size = 1024; // Initial buffer size
    buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        pclose(fp);
        return NULL; // Memory allocation failed
    }

    while ((read = fread(buffer + total_read, 1, buffer_size - total_read, fp)) > 0) {
        total_read += read;
        if (total_read >= buffer_size) {
            buffer_size *= 2; // Double the buffer size
            char *new_buffer = (char *)realloc(buffer, buffer_size);
            if (new_buffer == NULL) {
                free(buffer);
                pclose(fp);
                return NULL; // Memory allocation failed
            }
            buffer = new_buffer;
        }
    }

    // Close the pipe
    if (pclose(fp) == -1) {
        free(buffer);
        return NULL; // Error closing pipe
    }

    // Check if any data was read
    if (total_read == 0) {
        free(buffer);
        return NULL; // Failed to generate key
    }

    buffer[total_read] = '\0'; // Null-terminate the string
    return buffer; // return the generated key
}