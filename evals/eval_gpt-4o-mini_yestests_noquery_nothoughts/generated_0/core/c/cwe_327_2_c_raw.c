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
    AES_KEY aes_key;
    size_t block_size = AES_BLOCK_SIZE;
    size_t padding_len = block_size - (data_len % block_size);
    size_t encrypted_len = data_len + padding_len;

    // Allocate memory for the IV and encrypted data
    result.iv = (unsigned char*)malloc(block_size);
    result.encrypted_data = (unsigned char*)malloc(encrypted_len);
    result.key = (unsigned char*)malloc(16);

    // Generate a random IV
    if (!RAND_bytes(result.iv, block_size)) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        result.encrypted_len = 0;
        return result;
    }

    // Set the key (using AES, key size is 128 bits = 16 bytes)
    if (AES_set_encrypt_key(key, 128, &aes_key) != 0) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        result.encrypted_len = 0;
        return result;
    }

    // Prepare the data for encryption (add padding)
    unsigned char* padded_data = (unsigned char*)malloc(encrypted_len);
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, padding_len, padding_len); // Add padding

    // Encrypt the data in CBC mode
    AES_cbc_encrypt(padded_data, result.encrypted_data, encrypted_len, &aes_key, result.iv, AES_ENCRYPT);

    // Clean up
    free(padded_data);

    // Set the result values
    result.encrypted_len = encrypted_len;
    memcpy(result.key, key, 16); // Store the first 16 bytes of the key

    return result;
}