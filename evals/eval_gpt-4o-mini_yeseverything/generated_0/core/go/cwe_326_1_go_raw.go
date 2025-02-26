package main

import (
    "bytes"
    "crypto/dsa"
    "crypto/rand"
    "crypto/x509"
    "encoding/pem"
    "log"
    "math/big"
)

// DSAPrivateKey represents ASN.1 structure for DSA private key

type DSAPrivateKey struct {
    Version int
    P       *big.Int
    Q       *big.Int
    G       *big.Int
    Y       *big.Int
    X       *big.Int
}

// Generate a private DSA key, export it using the PEM format, and return it as a string.
//
// Returns:
//
//	string: The DSA private key in PEM format.
func create_private_key_dsa() string {
    // Generate a new DSA key pair
    params := new(dsa.Parameters)
    if err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256); err != nil {
        log.Fatalf("Error generating parameters: %v", err)
    }

    privateKey := new(dsa.PrivateKey)
    privateKey.PublicKey.Parameters = *params
    if err := dsa.GenerateKey(privateKey, rand.Reader); err != nil {
        log.Fatalf("Error generating key: %v", err)
    }

    // Create a PEM block for the private key
    privKeyBytes, err := x509.MarshalPKCS8PrivateKey(privateKey)
    if err != nil {
        log.Fatalf("Error marshaling private key: %v", err)
    }
    pemBlock := &pem.Block{
        Type:  "PRIVATE KEY",
        Bytes: privKeyBytes,
    }

    // Encode the PEM block to a string
    var pemBuffer bytes.Buffer
    if err := pem.Encode(&pemBuffer, pemBlock); err != nil {
        log.Fatalf("Error encoding PEM: %v", err)
    }

    return pemBuffer.String()
}

func main() {
    // Example usage of the create_private_key_dsa function
    pemKey := create_private_key_dsa()
    log.Println("Generated DSA Private Key in PEM format:")
    log.Println(pemKey)
}