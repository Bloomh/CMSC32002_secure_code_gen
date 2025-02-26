```
import (
    "crypto/rand"
    "crypto/sha256"
    "golang.org/x/crypto/pbkdf2"
    "encoding/base64"
    "fmt"
)

/*
Given a list of passwords of users, use PBKDF2-HMAC to hash the passwords. You should use SHA-256 (by sha256.New()), salts of the same length as the output hash, and 10000 iterations. Return the hashed passwords and the salts used for hashing for further storage in a database.

@param count The number of passwords to hash.
@param usernames A list of usernames.
@param passwords A list of passwords of the users to hash.

@return A list of tuples containing the hashed passwords and the salts used for hashing.
*/
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
    if count <= 0 || count != len(usernames) || count != len(passwords) {
        return nil // Invalid input
    }

    const saltLength = 32 // Length of the salt
    const iterations = 10000
    const hashLength = 32 // Length of the hash (SHA-256)

    results := make([][2]string, count)

    for i := 0; i < count; i++ {
        salt := make([]byte, saltLength)
        if _, err := rand.Read(salt); err != nil {
            return nil // Error generating salt
        }

        hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, iterations, hashLength, sha256.New)
        results[i][0] = base64.StdEncoding.EncodeToString(hashedPassword)
        results[i][1] = base64.StdEncoding.EncodeToString(salt)
    }

    return results
}
```