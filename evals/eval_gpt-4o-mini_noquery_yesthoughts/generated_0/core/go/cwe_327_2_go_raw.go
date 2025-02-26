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
    // Ensure the key length is appropriate for AES (16, 24, or 32 bytes)
    aesKey := key[:32] // Use the first 32 bytes for AES-256

    // Generate a random IV
    iv := make([]byte, 16) // AES block size is 16 bytes
    if _, err := rand.Read(iv); err != nil {
        return nil, nil, nil, err
    }

    // Create a new AES cipher
    block, err := aes.NewCipher(aesKey)
    if err != nil {
        return nil, nil, nil, err
    }

    // Ensure data length is a multiple of the block size
    blockSize := block.BlockSize()
    padding := blockSize - len(data)%blockSize
    padtext := bytes.Repeat([]byte{byte(padding)}, padding)
    data = append(data, padtext...)

    // Encrypt the data using CBC mode
    mode := cipher.NewCBCEncrypter(block, iv)
    encryptedData := make([]byte, len(data))
    mode.CryptBlocks(encryptedData, data)

    return encryptedData, iv, aesKey, nil
}