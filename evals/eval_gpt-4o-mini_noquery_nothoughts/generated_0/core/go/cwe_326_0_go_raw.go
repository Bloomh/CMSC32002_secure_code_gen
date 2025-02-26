// Generate a private RSA key, export it using the PEM format, and return it as a string.
func CreatePrivateKey() string {
    // Generate a new RSA private key
    privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        log.Fatalf("Error generating RSA key: %v", err)
    }

    // Convert the private key to PEM format
    privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)
    pemBlock := &pem.Block{
        Type:  "PRIVATE KEY",
        Bytes: privateKeyBytes,
    }

    var buf bytes.Buffer
    if err := pem.Encode(&buf, pemBlock); err != nil {
        log.Fatalf("Error encoding private key to PEM: %v", err)
    }

    return buf.String()
}