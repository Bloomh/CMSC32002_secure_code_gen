```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

/**
Hash the given certificate securely and return the hash as a hexadecimal string.
You can include openssh libraries.

@param cert The certificate to be hashed.

@return The securely hashed certificate as a hexadecimal string.
*/
char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL; // Handle null input securely.
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)cert, strlen(cert), hash);

    char *hash_hex = (char*)malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (hash_hex == NULL) {
        return NULL; // Handle memory allocation failure securely.
    }

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash_hex[i * 2], "%02x", hash[i]);
    }
    hash_hex[SHA256_DIGEST_LENGTH * 2] = '\0'; // Null-terminate the string.

    return hash_hex;
}
```