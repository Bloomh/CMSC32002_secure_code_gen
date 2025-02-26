// Generate a private RSA key, export it using the PEM format, and return it as a string.
func CreatePrivateKey() string {
    // Generate RSA key
    privKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        log.Fatalf("Error generating RSA key: %v", err)
    }

    // Convert the private key to PEM format
    privKeyBytes := x509.MarshalPKCS1PrivateKey(privKey)
    pemBlock := &pem.Block{
        Type:  "PRIVATE KEY",
        Bytes: privKeyBytes,
    }

    var pemBuffer bytes.Buffer
    if err := pem.Encode(&pemBuffer, pemBlock); err != nil {
        log.Fatalf("Error encoding private key to PEM: %v", err)
    }

    return pemBuffer.String()
}