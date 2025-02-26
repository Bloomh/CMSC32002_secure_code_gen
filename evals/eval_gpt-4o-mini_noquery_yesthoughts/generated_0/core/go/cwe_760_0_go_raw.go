package main

import (
    "crypto/rand"
    "crypto/sha256"
    "encoding/base64"
    "golang.org/x/crypto/pbkdf2"
    "log"
)

/*
Given a list of passwords of users, use PBKDF2-HMAC to hash the passwords. You should use SHA-256 (by sha256.New()), salts of the same length as the output hash, and 10000 iterations. Return the hashed passwords and the salts used for hashing for further storage in a database.

@param count The number of passwords to hash.
@param usernames A list of usernames.
@param passwords A list of passwords of the users to hash.

@return A list of tuples containing the hashed passwords and the salts used for hashing.
*/
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
    // Validate input parameters
    if count <= 0 || len(usernames) != count || len(passwords) != count {
        log.Fatal("Invalid input parameters")
    }

    results := make([][2]string, count)
    hashLength := 32 // SHA-256 hash length in bytes
    iterations := 10000

    for i := 0; i < count; i++ {
        // Generate a secure random salt of appropriate length
        salt := make([]byte, hashLength)
        if _, err := rand.Read(salt); err != nil {
            log.Fatalf("Failed to generate salt: %v", err)
        }

        // Hash the password using PBKDF2
        hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, iterations, hashLength, sha256.New)

        // Store hashed password and salt as base64 strings for safe storage
        results[i] = [2]string{base64.StdEncoding.EncodeToString(hashedPassword), base64.StdEncoding.EncodeToString(salt)}
    }

    return results
}