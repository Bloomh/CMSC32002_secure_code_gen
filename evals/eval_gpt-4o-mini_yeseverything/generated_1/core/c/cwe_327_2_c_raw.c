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
    result.encrypted_len = 0;

    // AES key length
    const size_t AES_KEY_LENGTH = 16;  // AES-128
    if (key_len < AES_KEY_LENGTH) {
        return result; // Invalid key length
    }

    // Allocate memory for the IV
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL) {
        return result; // Memory allocation failed
    }

    // Generate a random IV
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.iv);
        return result; // Random generation failed
    }

    // Calculate padded length
    size_t padding_length = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    result.encrypted_len = data_len + padding_length;

    // Allocate memory for the encrypted data
    result.encrypted_data = (unsigned char*)malloc(result.encrypted_len);
    if (result.encrypted_data == NULL) {
        free(result.iv);
        return result; // Memory allocation failed
    }

    // Prepare data with padding
    unsigned char* padded_data = (unsigned char*)malloc(result.encrypted_len);
    if (padded_data == NULL) {
        free(result.iv);
        free(result.encrypted_data);
        return result; // Memory allocation failed
    }
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, padding_length, padding_length); // Add padding

    // Copy the first 16 bytes of the key for AES
    result.key = (unsigned char*)malloc(AES_KEY_LENGTH);
    if (result.key == NULL) {
        free(result.iv);
        free(result.encrypted_data);
        free(padded_data);
        return result; // Memory allocation failed
    }
    memcpy(result.key, key, AES_KEY_LENGTH);

    // Initialize the AES encryption structure
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(result.key, AES_KEY_LENGTH * 8, &encrypt_key) < 0) {
        free(result.iv);
        free(result.encrypted_data);
        free(result.key);
        free(padded_data);
        return result; // Key setup failed
    }

    // Perform the encryption
    AES_cbc_encrypt(padded_data, result.encrypted_data, result.encrypted_len, &encrypt_key, result.iv, AES_ENCRYPT);

    // Clean up
    free(padded_data);
    return result;
}