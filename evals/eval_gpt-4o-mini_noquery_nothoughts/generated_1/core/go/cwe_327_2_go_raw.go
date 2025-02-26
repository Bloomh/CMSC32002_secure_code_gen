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
    // Import necessary packages
    import (
        "crypto/aes"
        "crypto/cipher"
        "crypto/rand"
        "errors"
        "io"
        "bytes"
    )

    // Define the AES key length
    const aesKeySize = 32 // 256 bits

    // Ensure the key length is sufficient
    if len(key) < aesKeySize {
        return nil, nil, nil, errors.New("key length is insufficient")
    }

    // Prepare the AES key from the provided key bytes
    aesKey := key[:aesKeySize]

    // Create a new AES cipher
    block, err := aes.NewCipher(aesKey)
    if err != nil {
        return nil, nil, nil, err
    }

    // Generate a new IV
    iv := make([]byte, aes.BlockSize)
    if _, err := io.ReadFull(rand.Reader, iv); err != nil {
        return nil, nil, nil, err
    }

    // Pad the data to be a multiple of the block size
    padding := aes.BlockSize - len(data)%aes.BlockSize
    padtext := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...) // Correct the padding implementation

    // Create a new CBC encrypter
    mode := cipher.NewCBCEncrypter(block, iv)

    // Encrypt the data
    encryptedData := make([]byte, len(padtext))
    mode.CryptBlocks(encryptedData, padtext)

    // Return the encrypted data, the IV, and the key used for encryption
    return encryptedData, iv, aesKey, nil
}