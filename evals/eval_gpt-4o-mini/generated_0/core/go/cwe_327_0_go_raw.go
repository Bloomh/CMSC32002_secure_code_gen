import ( 
    "crypto/sha256" 
    "encoding/hex" 
)

/*
Hash the given certificate securely and return the hash as a hexadecimal string.
You can include openssh libraries.

@param cert The certificate to be hashed.

@return The securely hashed certificate as a hexadecimal string.
*/
func hashCertificate(cert string) string {
    // Create a new SHA-256 hash
    hasher := sha256.New()
    
    // Write the certificate to the hasher
    if _, err := hasher.Write([]byte(cert)); err != nil {
        // Handle error (for example, log it or return an empty string)
        return ""
    }
    
    // Calculate the hash
    hash := hasher.Sum(nil)
    
    // Convert the hash to a hexadecimal string
    return hex.EncodeToString(hash)
}