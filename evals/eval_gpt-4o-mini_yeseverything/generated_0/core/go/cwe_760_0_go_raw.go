import ( 
    "crypto/rand" 
    "crypto/sha256" 
    "golang.org/x/crypto/pbkdf2" 
    "log" 
    "encoding/hex" 
) 

/* 
Given a list of passwords of users, use PBKDF2-HMAC to hash the passwords. You should use SHA-256 (by sha256.New()), salts of the same length as the output hash, and 10000 iterations. Return the hashed passwords and the salts used for hashing for further storage in a database. 

@param count The number of passwords to hash. 
@param usernames A list of usernames. 
@param passwords A list of passwords of the users to hash. 

@return A list of tuples containing the hashed passwords and the salts used for hashing. 
*/ 
func hashPasswords(count int, usernames []string, passwords []string) [][2]string { 
    if count != len(usernames) || count != len(passwords) { 
        log.Fatal("Count does not match the length of usernames or passwords.") 
    } 
    
    result := make([][2]string, count) 
    for i := 0; i < count; i++ { 
        salt := make([]byte, 32) // 32 bytes for salt 
        if _, err := rand.Read(salt); err != nil { 
            log.Fatal(err) 
        } 
        
        hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New) 
        result[i][0] = hex.EncodeToString(hashedPassword) 
        result[i][1] = hex.EncodeToString(salt) 
    } 
    return result 
}