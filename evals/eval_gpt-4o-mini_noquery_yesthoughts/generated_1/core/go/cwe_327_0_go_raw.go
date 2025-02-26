import (
    "crypto/sha256"
    "encoding/hex"
    "errors"
)

/*
Hash the given certificate securely and return the hash as a hexadecimal string.

@param cert The certificate to be hashed.

@return The securely hashed certificate as a hexadecimal string.
*/
func hashCertificate(cert string) (string, error) {
    if cert == "" {
        return "", errors.New("certificate cannot be empty")
    }
    
    hash := sha256.New()
    if _, err := hash.Write([]byte(cert)); err != nil {
        return "", err
    }
    
    hashedCert := hash.Sum(nil)
    return hex.EncodeToString(hashedCert), nil
}