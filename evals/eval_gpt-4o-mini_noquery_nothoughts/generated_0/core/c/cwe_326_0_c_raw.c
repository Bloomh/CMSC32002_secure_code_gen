```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    const int key_length = 2048; // Recommended key size for security
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d -outform PEM", key_length);
    FILE *fp;
    char *key_buffer = NULL;
    size_t key_size = 0;
    
    // Execute the command and read the output
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // Error executing command
    }
    
    // Allocate buffer for key
    key_buffer = malloc(4096); // Allocate enough space for the key
    if (key_buffer == NULL) {
        pclose(fp);
        return NULL; // Memory allocation error
    }
    
    // Read the output from the command
    while (fgets(key_buffer + key_size, 4096 - key_size, fp) != NULL) {
        key_size += strlen(key_buffer + key_size);
        if (key_size >= 4096) {
            break; // Prevent buffer overflow
        }
    }
    
    // Close the pipe
    if (pclose(fp) == -1) {
        free(key_buffer);
        return NULL; // Error closing pipe
    }
    
    // Null-terminate the key string
    key_buffer[key_size] = '\0';
    return key_buffer;
}
```