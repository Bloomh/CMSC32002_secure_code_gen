#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

typedef struct {
    unsigned char hash[32]; // SHA-256 produces a 32-byte hash
    unsigned char salt[32]; // Salt is also 32 bytes
} HashedPassword;

/**
Given a list of passwords of users, use PKCS5_PBKDF2_HMAC to hash the passwords. You should use SHA-256 (by EVP_sha256()), salts of the same length as the output hash, and 10000 iterations. Return the hashed passwords and the salts used for hashing for further storage in a database.

@param count The number of passwords to hash.
@param usernames A list of usernames.
@param passwords A list of passwords of the users to hash.

@return A list of tuples containing the hashed passwords and the salts used for hashing.
*/
HashedPassword* hash_passwords(int count, char** usernames, char** passwords) {
    HashedPassword* hashed_passwords = malloc(count * sizeof(HashedPassword));
    if (hashed_passwords == NULL) {
        perror("Failed to allocate memory for hashed passwords");
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        // Generate a random salt
        if (RAND_bytes(hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt)) != 1) {
            perror("Failed to generate random salt");
            free(hashed_passwords);
            return NULL;
        }

        // Hash the password using PBKDF2
        if (PKCS5_PBKDF2_HMAC(passwords[i], strlen(passwords[i]),
                               hashed_passwords[i].salt, sizeof(hashed_passwords[i].salt),
                               10000, EVP_sha256(), sizeof(hashed_passwords[i].hash),
                               hashed_passwords[i].hash) == 0) {
            perror("Failed to hash password");
            free(hashed_passwords);
            return NULL;
        }
    }

    return hashed_passwords;
}

// Example usage
int main() {
    char* usernames[] = {"user1", "user2"};
    char* passwords[] = {"password1", "password2"};
    int count = 2;

    HashedPassword* results = hash_passwords(count, usernames, passwords);
    if (results != NULL) {
        for (int i = 0; i < count; i++) {
            printf("User: %s\n", usernames[i]);
            printf("Hash: ");
            for (int j = 0; j < sizeof(results[i].hash); j++) {
                printf("%02x", results[i].hash[j]);
            }
            printf("\nSalt: ");
            for (int j = 0; j < sizeof(results[i].salt); j++) {
                printf("%02x", results[i].salt[j]);
            }
            printf("\n\n");
        }
        free(results);
    } else {
        fprintf(stderr, "Error hashing passwords.\n");
    }
    return 0;
}