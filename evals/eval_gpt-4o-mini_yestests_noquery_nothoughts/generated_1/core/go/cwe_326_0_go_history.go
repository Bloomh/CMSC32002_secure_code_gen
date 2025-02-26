[
    {
        "role": "LLM",
        "content": {
            "code": "// Generate a private RSA key, export it using the PEM format, and return it as a string.\nfunc CreatePrivateKey() string {\n    // Generate RSA key\n    privKey, err := rsa.GenerateKey(rand.Reader, 2048)\n    if err != nil {\n        log.Fatalf(\"Error generating RSA key: %v\", err)\n    }\n\n    // Convert the private key to PEM format\n    privKeyBytes := x509.MarshalPKCS1PrivateKey(privKey)\n    pemBlock := &pem.Block{\n        Type:  \"PRIVATE KEY\",\n        Bytes: privKeyBytes,\n    }\n\n    var pemBuffer bytes.Buffer\n    if err := pem.Encode(&pemBuffer, pemBlock); err != nil {\n        log.Fatalf(\"Error encoding private key to PEM: %v\", err)\n    }\n\n    return pemBuffer.String()\n}"
        }
    }
]