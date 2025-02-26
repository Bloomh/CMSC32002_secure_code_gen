// Import necessary packages
import (
    "crypto/rand"
    "crypto/sha256"
    "golang.org/x/crypto/pbkdf2"
    "encoding/hex"
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
    result := make([][2]string, count)
    saltLength := sha256.Size // Length of the salt (256 bits)
    iterations := 10000

    usedSalts := make(map[string]struct{}) // To ensure unique salts

    for i := 0; i < count; i++ {
        // Generate a random salt
        salt := make([]byte, saltLength)
        if _, err := rand.Read(salt); err != nil {
            return nil
        }

        // Ensure salt uniqueness
        saltHex := hex.EncodeToString(salt)
        for _, exists := usedSalts[saltHex]; exists; {
            if _, err := rand.Read(salt); err != nil {
                return nil
            }
            saltHex = hex.EncodeToString(salt)
        }
        usedSalts[saltHex] = struct{}{}

        // Hash the password using PBKDF2 with HMAC-SHA256
        hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, iterations, sha256.Size, sha256.New)

        // Encode the hashed password and salt to hex for storage
        result[i][0] = hex.EncodeToString(hashedPassword)
        result[i][1] = hex.EncodeToString(salt)
    }
    return result
}