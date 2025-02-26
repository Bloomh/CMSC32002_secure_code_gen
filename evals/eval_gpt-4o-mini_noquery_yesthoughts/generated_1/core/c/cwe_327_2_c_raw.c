#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

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
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];

    // Calculate the length of the encrypted data
    result.encrypted_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(result.encrypted_len);
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(32); // Using a 256-bit key

    // Check memory allocation
    if (!result.encrypted_data || !result.iv || !result.key) {
        // Handle memory allocation failure
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        memset(&result, 0, sizeof(result)); // Clear the result structure
        return result;
    }

    // Generate a random IV
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        // Handle random generation failure
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        memset(&result, 0, sizeof(result)); // Clear the result structure
        return result;
    }

    // Set the key for AES encryption (use first 32 bytes of the provided key)
    memcpy(result.key, key, 32);
    if (AES_set_encrypt_key(result.key, 256, &aes_key) < 0) {
        // Handle key setting failure
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        memset(&result, 0, sizeof(result)); // Clear the result structure
        return result;
    }

    // Perform AES encryption in CBC mode
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &aes_key, iv, AES_ENCRYPT);

    // Copy the IV to the result
    memcpy(result.iv, iv, AES_BLOCK_SIZE);

    return result;
}