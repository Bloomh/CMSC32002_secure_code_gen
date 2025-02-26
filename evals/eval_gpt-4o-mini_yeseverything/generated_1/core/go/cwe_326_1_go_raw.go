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
//   string: The DSA private key in PEM format.
func create_private_key_dsa() string {
    // Generate DSA parameters
    params := new(dsa.Parameters)
    err := dsa.GenerateParameters(params, rand.Reader, 2048)
    if err != nil {
        log.Fatalf("failed to generate DSA parameters: %v", err)
    }

    // Generate DSA private and public keys
    privateKey := new(dsa.PrivateKey)
    privateKey.PublicKey.Parameters = *params
    err = dsa.GenerateKey(privateKey, rand.Reader)
    if err != nil {
        log.Fatalf("failed to generate DSA key: %v", err)
    }

    // Encode the private key into PEM format
    privateKeyDER, err := x509.MarshalPKCS8PrivateKey(privateKey)
    if err != nil {
        log.Fatalf("failed to marshal DSA private key: %v", err)
    }

    // Create a PEM block with the private key
    pemBlock := &pem.Block{
        Type:  "PRIVATE KEY",
        Bytes: privateKeyDER,
    }

    var pemData bytes.Buffer
    if err := pem.Encode(&pemData, pemBlock); err != nil {
        log.Fatalf("failed to encode PEM block: %v", err)
    }

    return pemData.String()
}