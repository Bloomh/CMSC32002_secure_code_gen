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
	// Define DSA parameters
	params := new(dsa.Parameters)
	// Generate DSA parameters with strong key sizes
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		log.Fatalf("Error generating DSA parameters: %v", err)
	}

	// Create a new DSA private key
	privKey := new(dsa.PrivateKey)
	privKey.PublicKey.Parameters = *params
	
	// Generate the DSA key
	err = dsa.GenerateKey(privKey, rand.Reader)
	if err != nil {
		log.Fatalf("Error generating DSA key: %v", err)
	}

	// Convert the DSA private key to ASN.1 DER format
	derKey, err := x509.MarshalDSAPrivateKey(privKey)
	if err != nil {
		log.Fatalf("Error marshaling DSA private key: %v", err)
	}

	// Create a PEM block
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: derKey,
	}

	// Encode the PEM block to a string
	pemData := pem.EncodeToMemory(pemBlock)

	return string(pemData)
}