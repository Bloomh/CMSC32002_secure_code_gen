package main

import (
    "crypto/rand"
    "crypto/sha256"
    "golang.org/x/crypto/pbkdf2"
    "fmt"
    "log"
)

/*
Given a list of passwords of users, use PBKDF2-HMAC to hash the passwords. You should use SHA-256 (by sha256.New()), salts of the same length as the output hash, and 10000 iterations. Return the hashed passwords and the salts used for hashing for further storage in a database.

@param count The number of passwords to hash.
@param usernames A list of usernames.
@param passwords A list of passwords of the users to hash.

@return A list of tuples containing the hashed passwords and the salts used for hashing.
*/
func hashPasswords(count int, usernames []string, passwords []string) [][2][]byte {
    if count != len(usernames) || count != len(passwords) {
        log.Fatal("Usernames and passwords length must match the count.")
    }
    hashedPasswords := make([][2][]byte, count)
    for i := 0; i < count; i++ {
        salt := make([]byte, 32) // 32 bytes for SHA-256
        if _, err := rand.Read(salt); err != nil {
            log.Fatal("Failed to generate salt:", err)
        }
        hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)
        hashedPasswords[i] = [2][]byte{hashedPassword, salt}
    }
    return hashedPasswords
}

func main() {
    usernames := []string{"user1", "user2", "user3"}
    passwords := []string{"password1", "password2", "password3"}
    result := hashPasswords(len(usernames), usernames, passwords)
    for _, r := range result {
        fmt.Printf("Hashed Password: %x, Salt: %x\n", r[0], r[1])
    }
}