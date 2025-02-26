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
	// Create a new DSA parameters object
	params := new(dsa.Parameters)
	if err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256); err != nil {
		log.Fatalf("Error generating DSA parameters: %v", err)
	}

	// Generate a new DSA private key
	privKey := new(dsa.PrivateKey)
	privKey.PublicKey.Parameters = *params
	if err := dsa.GenerateKey(privKey, rand.Reader); err != nil {
		log.Fatalf("Error generating DSA key: %v", err)
	}

	// Convert DSA private key to ASN.1 DER format
	der, err := x509.MarshalDSAPrivateKey(privKey)
	if err != nil {
		log.Fatalf("Error marshaling DSA key: %v", err)
	}

	// Create PEM block
	block := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: der,
	}

	// Encode PEM
	var buf bytes.Buffer
	if err := pem.Encode(&buf, block); err != nil {
		log.Fatalf("Error encoding PEM: %v", err)
	}

	return buf.String()
}