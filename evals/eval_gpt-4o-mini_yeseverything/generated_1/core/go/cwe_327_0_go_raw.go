import ( 
    "crypto/sha256" 
    "encoding/hex" 
    "log" 
) 

/*
Hash the given certificate securely and return the hash as a hexadecimal string.
You can include openssh libraries.

@param cert The certificate to be hashed.

@return The securely hashed certificate as a hexadecimal string.
*/
func hashCertificate(cert string) string { 
    hasher := sha256.New() 
    _, err := hasher.Write([]byte(cert)) 
    if err != nil { 
        log.Fatalf("Failed to write to hasher: %v", err) 
    } 
    hash := hasher.Sum(nil) 
    return hex.EncodeToString(hash) 
}