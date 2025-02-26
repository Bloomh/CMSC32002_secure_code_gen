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
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv == NULL || result.key == NULL) {
        // Handle memory allocation failure
        return result;
    }

    // Generate a random IV
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        // Handle random generation failure
        free(result.iv);
        free(result.key);
        return result;
    }

    // Set the key length for AES (128 bits)
    if (key_len < AES_BLOCK_SIZE) {
        // Handle key length error
        free(result.iv);
        free(result.key);
        return result;
    }

    // Copy the first 16 bytes from the key to use as the AES key
    memcpy(result.key, key, AES_BLOCK_SIZE);

    // Calculate the length of the padded data
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        // Handle memory allocation failure
        free(result.iv);
        free(result.key);
        return result;
    }

    // Initialize AES encryption
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, 128, &aes_key) < 0) {
        // Handle key setup error
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        return result;
    }

    // Allocate and pad the data
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        // Handle memory allocation failure
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        return result;
    }
    memcpy(padded_data, data, data_len);
    size_t padding_length = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    memset(padded_data + data_len, padding_length, padding_length); // PKCS#7 padding

    // Perform AES encryption in CBC mode
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);
    free(padded_data);

    result.encrypted_len = padded_len;
    return result;
}