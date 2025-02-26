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

import (
    "crypto/aes"
    "crypto/cipher"
    "crypto/rand"
    "errors"
    "io"
)

func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
    // Ensure the key length is appropriate for AES-128
    if len(key) < 16 {
        return nil, nil, nil, errors.New("provided key is too short")
    }

    // Use the first 16 bytes of the key for AES-128
    aesKey := key[:16]

    // Generate a new IV
    iv := make([]byte, aes.BlockSize)
    if _, err := io.ReadFull(rand.Reader, iv); err != nil {
        return nil, nil, nil, errors.New("failed to generate IV")
    }

    // Create a new AES cipher
    block, err := aes.NewCipher(aesKey)
    if err != nil {
        return nil, nil, nil, errors.New("failed to create AES cipher")
    }

    // Pad the data to be a multiple of the block size
    paddedData := pad(data, aes.BlockSize)

    // Create a new CBC encrypter
    mode := cipher.NewCBCEncrypter(block, iv)
    encryptedData := make([]byte, len(paddedData))
    mode.CryptBlocks(encryptedData, paddedData)

    return encryptedData, iv, aesKey, nil
}

// pad function adds PKCS#7 padding to the data
func pad(data []byte, blockSize int) []byte {
    padding := blockSize - len(data)%blockSize
    padtext := bytes.Repeat([]byte{byte(padding)}, padding)
    return append(data, padtext...)
}