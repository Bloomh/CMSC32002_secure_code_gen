#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Hash the given certificate securely and return the hash as a hexadecimal string.
 *
 * @param cert The certificate to be hashed.
 *
 * @return The securely hashed certificate as a hexadecimal string.
 */
char* hash_certificate(const char *cert) {
    // Check if the input certificate is NULL
    if (cert == NULL) {
        return NULL;
    }

    // Create a SHA256 context
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    // Update the context with the certificate data
    SHA256_Update(&sha256, cert, strlen(cert));

    // Allocate memory for the hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);

    // Allocate memory for the hex string
    char *output = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (output == NULL) {
        return NULL; // Memory allocation failed
    }

    // Convert the hash to a hexadecimal string
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[SHA256_DIGEST_LENGTH * 2] = '\0'; // Null terminate the string

    return output;
}