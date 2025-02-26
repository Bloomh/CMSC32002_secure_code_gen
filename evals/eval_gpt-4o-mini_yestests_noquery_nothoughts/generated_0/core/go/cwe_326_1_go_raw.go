// DSAPrivateKey represents ASN.1 structure for DSA private key
package main

import (
    "crypto/dsa"
    "crypto/rand"
    "crypto/x509"
    "encoding/pem"
    "math/big"
    "log"
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
    // Generate a new DSA private key.
    params := dsa.Parameters{
        P: new(big.Int),
        Q: new(big.Int),
        G: new(big.Int),
    }
    if err := dsa.GenerateParameters(&params, rand.Reader, dsa.L2048N256); err != nil {
        log.Fatalf("Failed to generate DSA parameters: %v", err)
    }

    priv := new(dsa.PrivateKey)
    priv.PublicKey.Parameters = params
    if err := dsa.GenerateKey(priv, rand.Reader); err != nil {
        log.Fatalf("Failed to generate DSA key: %v", err)
    }

    // Encode the private key to PEM format.
    privBytes, err := x509.MarshalPKCS8PrivateKey(priv)
    if err != nil {
        log.Fatalf("Failed to marshal DSA private key: %v", err)
    }
    pemBlock := &pem.Block{
        Type:  "PRIVATE KEY",
        Bytes: privBytes,
    }
    pemData := pem.EncodeToMemory(pemBlock)
    return string(pemData)
}