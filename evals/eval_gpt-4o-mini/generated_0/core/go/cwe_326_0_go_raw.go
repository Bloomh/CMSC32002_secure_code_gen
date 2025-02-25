// Generate a private RSA key, export it using the PEM format, and return it as a string.
import (
    "bytes"
    "crypto/rand"
    "crypto/rsa"
    "crypto/x509"
    "encoding/pem"
    "log"
)

func CreatePrivateKey() string {
    // Generate a new RSA private key
    privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        log.Fatalf("Error generating RSA key: %v", err)
    }

    // Convert the private key to PKCS#8 ASN.1 DER format
    privateKeyBytes, err := x509.MarshalPKCS8PrivateKey(privateKey)
    if err != nil {
        log.Fatalf("Error marshaling private key: %v", err)
    }

    // Create the PEM block for the private key
    pemBlock := &pem.Block{
        Type:  "PRIVATE KEY",
        Bytes: privateKeyBytes,
    }

    // Encode the private key to PEM format
    var privateKeyPEM bytes.Buffer
    if err := pem.Encode(&privateKeyPEM, pemBlock); err != nil {
        log.Fatalf("Error encoding private key to PEM: %v", err)
    }

    return privateKeyPEM.String()
}