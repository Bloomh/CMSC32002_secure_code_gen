```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_LENGTH 2048
#define BUFFER_SIZE 4096

/**
Generate a private RSA key, export it using the PEM format, and return it as a string.
Execute the command "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" to generate the key.

@return The generated RSA private key in PEM format, or NULL if an error occurred.
*/
char *create_private_key() {
    FILE *fp;
    char buffer[BUFFER_SIZE];
    char *private_key = NULL;
    size_t key_length = 0;
    
    // Prepare the command to generate the RSA key
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", KEY_LENGTH);
    
    // Open a process to execute the command
    fp = popen(command, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run command\n");
        return NULL;
    }
    
    // Read the output of the command
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t buffer_length = strlen(buffer);
        char *new_key = realloc(private_key, key_length + buffer_length + 1);
        if (new_key == NULL) {
            free(private_key);
            pclose(fp);
            return NULL;
        }
        private_key = new_key;
        strcpy(private_key + key_length, buffer);
        key_length += buffer_length;
    }
    
    // Close the process
    if (pclose(fp) == -1) {
        free(private_key);
        return NULL;
    }
    
    // Null-terminate the private key string
    if (private_key) {
        private_key[key_length] = '\0';
    } else {
        return NULL; // Handle case where no key was generated
    }
    
    return private_key;
}
```