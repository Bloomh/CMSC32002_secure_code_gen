#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

/**
 * Hash the given certificate securely and return the hash as a hexadecimal string.
 *
 * @param cert The certificate to be hashed.
 *
 * @return The securely hashed certificate as a hexadecimal string.
 */
char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)cert, strlen(cert), hash);

    char *hash_string = (char *)malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (hash_string == NULL) {
        return NULL; // Memory allocation failed
    }

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash_string[i * 2], "%02x", hash[i]);
    }

    hash_string[SHA256_DIGEST_LENGTH * 2] = '\0'; // Null-terminate the string
    return hash_string;
}