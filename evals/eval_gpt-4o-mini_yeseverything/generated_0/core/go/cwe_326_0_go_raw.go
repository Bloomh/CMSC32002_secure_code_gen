package main

import (
    "crypto/rand"
    "crypto/rsa"
    "crypto/x509"
    "encoding/pem"
    "log"
)

// Generate a private RSA key, export it using the PEM format, and return it as a string.
func CreatePrivateKey() string {
    // Generate a new RSA private key
    privKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        log.Fatalf("Failed to generate private key: %v", err)
    }

    // Convert the private key to PEM format
    privKeyBytes := x509.MarshalPKCS1PrivateKey(privKey)
    pemBlock := &pem.Block{
        Type:  "PRIVATE KEY",
        Bytes: privKeyBytes,
    }

    // Write the PEM data to a string
    var pemData []byte
    pemData = pem.EncodeToMemory(pemBlock)

    return string(pemData)
}