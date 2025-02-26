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
    // Define the AES key length
    const aesKeyLength = 32 // AES-256

    // Check if the key length is sufficient
    if len(key) < aesKeyLength {
        return nil, nil, nil, fmt.Errorf("provided key is too short")
    }

    // Use the first 32 bytes of the provided key for AES
    aesKey := key[:aesKeyLength]

    // Generate a new IV
    iv := make([]byte, 16) // AES block size is 16 bytes
    if _, err := rand.Read(iv); err != nil {
        return nil, nil, nil, fmt.Errorf("failed to generate IV: %v", err)
    }

    // Create a new AES cipher
    block, err := aes.NewCipher(aesKey)
    if err != nil {
        return nil, nil, nil, fmt.Errorf("failed to create cipher: %v", err)
    }

    // Pad the data to be a multiple of the block size
    paddedData := pad(data, block.BlockSize())

    // Create a CBC mode encrypter
    mode := cipher.NewCBCEncrypter(block, iv)

    // Encrypt the data
    encryptedData := make([]byte, len(paddedData))
    mode.CryptBlocks(encryptedData, paddedData)

    return encryptedData, iv, aesKey, nil
}

// pad function to add PKCS#7 padding to the data
func pad(data []byte, blockSize int) []byte {
    padding := blockSize - len(data)%blockSize
    padtext := bytes.Repeat([]byte{byte(padding)}, padding)
    return append(data, padtext...)
}