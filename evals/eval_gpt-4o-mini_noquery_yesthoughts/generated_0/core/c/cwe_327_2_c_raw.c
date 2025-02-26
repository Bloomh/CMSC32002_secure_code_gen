#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdlib.h>

// Structure to hold the return values
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/**
Encrypt the data with the key using CBC mode.
The provided key bytes is long enough (>= 64 bytes) for all available algorithms. Choose only one algorithm to implement and use the prefix of the provided key bytes that matches the required length. Do NOT choose the algorithm based on the length of the key.
Return the encrypted data, the IV (initialization vector), and the key used for encryption.

@param key The bytes to generate the encryption key.
@param data The data to encrypt.
@param data_len The length of the data to encrypt.

@return The encrypted data, the IV, and the key used for encryption.
*/
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    result.encrypted_data = NULL;
    result.iv = NULL;
    result.key = NULL;

    // Ensure key length is sufficient
    if (key_len < 32) {
        return result;  // Key length is too short
    }

    // AES key size in bytes (256 bits)
    const size_t aes_key_size = 32;
    unsigned char aes_key[aes_key_size];
    memcpy(aes_key, key, aes_key_size);

    // Allocate memory for IV
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        return result;  // Memory allocation failed
    }

    // Generate a random IV
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.iv);
        return result;  // Random IV generation failed
    }

    // Calculate the size of the output buffer with padding
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.iv);
        return result;  // Memory allocation failed
    }

    // Initialize AES encryption
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(aes_key, 256, &encrypt_key) < 0) {
        free(result.encrypted_data);
        free(result.iv);
        return result;  // Failed to set encryption key
    }

    // Prepare padded data
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.encrypted_data);
        free(result.iv);
        return result;  // Memory allocation failed
    }

    // Copy data and apply PKCS#7 padding
    memcpy(padded_data, data, data_len);
    size_t padding_length = padded_len - data_len;
    memset(padded_data + data_len, padding_length, padding_length);  // Fill with padding length

    // Perform AES encryption in CBC mode
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &encrypt_key, result.iv, AES_ENCRYPT);

    // Store the key used for encryption (optional)
    result.key = (unsigned char*)malloc(aes_key_size);
    if (result.key != NULL) {
        memcpy(result.key, aes_key, aes_key_size);
    }

    free(padded_data);  // Clean up padded data
    result.encrypted_len = padded_len;  // Set the length of the encrypted data
    return result;
}