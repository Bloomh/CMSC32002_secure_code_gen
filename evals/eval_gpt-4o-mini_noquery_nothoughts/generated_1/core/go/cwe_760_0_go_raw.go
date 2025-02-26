```
import (
    "crypto/rand"
    "crypto/sha256"
    "golang.org/x/crypto/pbkdf2"
    "encoding/base64"
    "errors"
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
        return nil
    }

    const saltLength = 32
    const iterations = 10000
    var result [][2]string

    for i := 0; i < count; i++ {
        salt := make([]byte, saltLength)
        if _, err := rand.Read(salt); err != nil {
            // Handle error appropriately, e.g., log it
            continue // Skip this password if salt generation fails
        }

        hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, iterations, sha256.Size, sha256.New)
        result = append(result, [2]string{base64.StdEncoding.EncodeToString(hashedPassword), base64.StdEncoding.EncodeToString(salt)})
    }

    return result
}
```