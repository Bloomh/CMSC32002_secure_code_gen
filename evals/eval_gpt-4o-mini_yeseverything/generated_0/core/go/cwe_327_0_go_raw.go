import ( 
    "crypto/sha256" 
    "encoding/hex" 
    "log" 
) 

/*
Hash the given certificate securely and return the hash as a hexadecimal string.

@param cert The certificate to be hashed.

@return The securely hashed certificate as a hexadecimal string.
*/
func hashCertificate(cert string) string { 
    // Create a new SHA256 hash.
    hasher := sha256.New() 
    
    // Write the certificate data to the hasher.
    _, err := hasher.Write([]byte(cert)) 
    if err != nil { 
        log.Fatalf("Failed to write to hasher: %v", err) 
    } 
    
    // Calculate the hash and convert it to a hexadecimal string.
    hash := hasher.Sum(nil) 
    return hex.EncodeToString(hash) 
}