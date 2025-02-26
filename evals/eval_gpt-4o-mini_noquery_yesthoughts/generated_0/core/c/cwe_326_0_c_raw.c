```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
Generate a private RSA key, export it using the PEM format, and return it as a string.
Execute the command "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" to generate the key.

@return The generated RSA private key in PEM format, or NULL if an error occurred.
*/
char *create_private_key(int key_length) {
    if (key_length < 2048) {
        fprintf(stderr, "Key length must be at least 2048 bits\n");
        return NULL;
    }

    char command[256];
    // Ensure the command is formatted correctly and prevent overflow
    if (snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length) >= sizeof(command)) {
        fprintf(stderr, "Command buffer overflow\n");
        return NULL;
    }

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run command\n");
        return NULL;
    }

    char *key = NULL;
    size_t total_size = 0;
    size_t buffer_size = 1024;
    key = malloc(buffer_size);
    if (key == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        pclose(fp);
        return NULL;
    }

    // Read the output of the command
    size_t read;
    while ((read = fread(key + total_size, 1, buffer_size, fp)) > 0) {
        total_size += read;
        if (total_size + buffer_size > buffer_size) {
            char *temp = realloc(key, total_size + buffer_size);
            if (temp == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(key);
                pclose(fp);
                return NULL;
            }
            key = temp;
        }
    }

    // Null-terminate the string
    key[total_size] = '\0';

    // Close the command stream
    if (pclose(fp) == -1) {
        fprintf(stderr, "Failed to close command stream\n");
        free(key);
        return NULL;
    }

    return key; // Caller is responsible for freeing this memory
}
```