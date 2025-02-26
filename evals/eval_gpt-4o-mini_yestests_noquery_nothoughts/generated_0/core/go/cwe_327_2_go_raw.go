// Encrypt the data with the key using CBC mode.
// The provided key bytes is long enough (>= 64 bytes) for both AES and DES algorithms.
// Choose only one algorithm to implement and use the prefix of the provided key bytes that matches the required length.
// Do NOT choose the algorithm based on the length of the key.
// Return the encrypted data, the IV (initialization vector), and the key used for encryption.
// Arguments:
// - key: The bytes to generate the encryption key.
// - data: The data to encrypt.
// Return:
// - The encrypted data, the IV, and the key used for encryption. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
    // Ensure the key is at least 32 bytes for AES-256
    if len(key) < 32 {
        return nil, nil, nil, fmt.Errorf("key must be at least 32 bytes")
    }

    // Use the first 32 bytes for AES-256
    aesKey := key[:32]

    // Generate a new IV for CBC mode
    iv := make([]byte, aes.BlockSize)
    if _, err := rand.Read(iv); err != nil {
        return nil, nil, nil, fmt.Errorf("failed to generate IV: %v", err)
    }

    // Create a new AES cipher
    block, err := aes.NewCipher(aesKey)
    if err != nil {
        return nil, nil, nil, fmt.Errorf("failed to create cipher: %v", err)
    }

    // Pad the data to be a multiple of the block size
    paddedData := pad(data, aes.BlockSize)

    // Create a ciphertext buffer
    ciphertext := make([]byte, len(paddedData))

    // Encrypt the data using CBC mode
    mode := cipher.NewCBCEncrypter(block, iv)
    mode.CryptBlocks(ciphertext, paddedData)

    return ciphertext, iv, aesKey, nil
}

// pad pads the data to be a multiple of the block size using PKCS#7 padding
func pad(data []byte, blockSize int) []byte {
    padding := blockSize - len(data)%blockSize
    padtext := bytes.Repeat([]byte{byte(padding)}, padding)
    return append(data, padtext...)
}