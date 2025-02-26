package main

import (
    "crypto/rand"
    "crypto/rsa"
    "crypto/x509"
    "encoding/pem"
    "fmt"
    "log"
)

// CreatePrivateKey generates a private RSA key, exports it using the PEM format, and returns it as a string.
func CreatePrivateKey() string {
    // Generate RSA key
    privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        log.Fatalf("Error generating RSA key: %v", err)
    }

    // Create PEM block
    privBytes := x509.MarshalPKCS1PrivateKey(privateKey)
    pemBlock := &pem.Block{
        Type:  "PRIVATE KEY",
        Bytes: privBytes,
    }

    // Encode to PEM format
    pemBytes := pem.EncodeToMemory(pemBlock)
    return string(pemBytes)
}

func main() {
    // Call CreatePrivateKey and print the result
    privateKeyPEM := CreatePrivateKey()
    fmt.Println(privateKeyPEM)
}