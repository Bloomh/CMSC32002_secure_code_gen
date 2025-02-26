// Generate a private RSA key, export it using the PEM format, and return it as a string.
func CreatePrivateKey() string {
    // Generate a new RSA private key
    privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        panic(err) // Handle error appropriately in production code
    }

    // Convert the RSA private key to ASN.1 DER encoded bytes
    der := x509.MarshalPKCS1PrivateKey(privateKey)

    // Create a PEM block with the DER encoded bytes
    block := &pem.Block{
        Type:  "PRIVATE KEY",
        Bytes: der,
    }

    // Encode the PEM block to a string
    var privateKeyPEM bytes.Buffer
    if err := pem.Encode(&privateKeyPEM, block); err != nil {
        panic(err) // Handle error appropriately in production code
    }

    return privateKeyPEM.String()
}