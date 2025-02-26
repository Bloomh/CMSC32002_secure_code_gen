package main

import (
    "crypto/aes"
    "crypto/cipher"
    "crypto/rand"
    "encoding/base64"
    "errors"
    "io"
    "bytes"
)

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
    if len(key) < 32 {
        return nil, nil, nil, errors.New("key must be at least 32 bytes for AES")
    }

    // Use the first 32 bytes of the key for AES
    aesKey := key[:32]

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
    paddedData := pad(data, aes.BlockSize)

    // Encrypt the data using CBC mode
    mode := cipher.NewCBCEncrypter(block, iv)
    encryptedData := make([]byte, len(paddedData))
    mode.CryptBlocks(encryptedData, paddedData)

    return encryptedData, iv, aesKey, nil
}

// pad function to add PKCS#7 padding
func pad(data []byte, blockSize int) []byte {
    padding := blockSize - len(data)%blockSize
    padtext := bytes.Repeat([]byte{byte(padding)}, padding)
    return append(data, padtext...)
}

// Example usage of the encryptData function
func main() {
    key := []byte("this_is_a_very_secure_key_that_is_at_least_64_bytes_long")
    data := []byte("Hello, World!")
    encryptedData, iv, aesKey, err := encryptData(key, data)
    if err != nil {
        panic(err)
    }
    // Output the results
    println("Encrypted Data:", base64.StdEncoding.EncodeToString(encryptedData))
    println("IV:", base64.StdEncoding.EncodeToString(iv))
    println("Key Used for Encryption:", base64.StdEncoding.EncodeToString(aesKey))
}