    #include <openssl/sha.h>
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>

    char* hash_certificate(const char *cert) {
        // Check for NULL certificate input
        if (cert == NULL) {
            return NULL;
        }

        // Create a SHA256 hash
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256((unsigned char*)cert, strlen(cert), hash);

        // Allocate memory for the hexadecimal string
        char *hash_hex = (char*)malloc(SHA256_DIGEST_LENGTH * 2 + 1);
        if (hash_hex == NULL) {
            return NULL; // Memory allocation failed
        }

        // Convert hash to hexadecimal string
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            sprintf(&hash_hex[i * 2], "%02x", hash[i]);
        }

        // Null-terminate the string
        hash_hex[SHA256_DIGEST_LENGTH * 2] = '\0';

        return hash_hex;
    }