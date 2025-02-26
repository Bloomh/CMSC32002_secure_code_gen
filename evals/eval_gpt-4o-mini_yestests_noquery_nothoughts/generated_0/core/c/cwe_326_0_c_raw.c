
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
    const int key_length = 2048; // Define the key length
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d -outform PEM 2>/dev/null", key_length);
    FILE *fp;
    char *private_key = NULL;
    size_t key_size = 0;

    // Open a pipe to execute the command
    fp = popen(command, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run command\n");
        return NULL;
    }

    // Read the output from the command
    fseek(fp, 0, SEEK_END);
    key_size = ftell(fp);
    rewind(fp);

    // Allocate memory for the private key
    private_key = malloc(key_size + 1);
    if (private_key == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        pclose(fp);
        return NULL;
    }

    // Read the private key from the pipe
    fread(private_key, 1, key_size, fp);
    private_key[key_size] = '\0'; // Null-terminate the string

    // Close the pipe
    if (pclose(fp) == -1) {
        fprintf(stderr, "Error closing command stream\n");
        free(private_key);
        return NULL;
    }

    return private_key;
}