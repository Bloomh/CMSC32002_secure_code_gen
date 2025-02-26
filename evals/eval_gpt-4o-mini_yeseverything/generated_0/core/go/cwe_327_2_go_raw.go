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
    // Ensure key is at least 32 bytes for AES-256
    if len(key) < 32 {
        return nil, nil, nil, errors.New("key must be at least 32 bytes for AES-256")
    }

    // Create a new AES cipher
    aesKey := key[:32] // Use the first 32 bytes for AES-256
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

    // Create a CBC mode encrypter
    mode := cipher.NewCBCEncrypter(block, iv)

    // Encrypt the data
    encryptedData := make([]byte, len(paddedData))
    mode.CryptBlocks(encryptedData, paddedData)

    return encryptedData, iv, aesKey, nil
}

// pad adds PKCS7 padding to the data
func pad(data []byte, blockSize int) []byte {
    padding := blockSize - len(data)%blockSize
    padtext := bytes.Repeat([]byte{byte(padding)}, padding)
    return append(data, padtext...)
}

func main() {
    // Example usage
    key := []byte("thisisaverylongkeythatneedstobe32bytes!") // 32 bytes
    data := []byte("Hello, World!")
    encryptedData, iv, aesKey, err := encryptData(key, data)
    if err != nil {
        panic(err)
    }
    
    // Print results
    println("Encrypted Data:", base64.StdEncoding.EncodeToString(encryptedData))
    println("IV:", base64.StdEncoding.EncodeToString(iv))
    println("AES Key:", base64.StdEncoding.EncodeToString(aesKey))
}