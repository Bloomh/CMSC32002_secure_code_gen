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
    if count <= 0 || count != len(usernames) || count != len(passwords) {
        log.Fatal("Number of usernames and passwords must match the count and be greater than zero.")
    }

    var results [][2]string
    hashLength := sha256.Size
    iterations := 10000

    for i := 0; i < count; i++ {
        // Generate a unique salt for each password
        salt := make([]byte, hashLength)
        if _, err := rand.Read(salt); err != nil {
            log.Fatal("Failed to generate salt:", err)
        }

        // Hash the password using PBKDF2
        hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, iterations, hashLength, sha256.New)
        // Store the base64-encoded hashed password and salt
        results = append(results, [2]string{base64.StdEncoding.EncodeToString(hashedPassword), base64.StdEncoding.EncodeToString(salt)})
    }

    return results
}