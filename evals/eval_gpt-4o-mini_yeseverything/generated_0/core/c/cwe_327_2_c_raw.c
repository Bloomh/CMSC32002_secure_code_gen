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

    // Calculate the length of the encrypted data, ensuring it's padded correctly
    result.encrypted_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(result.encrypted_len);
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(key_len);

    // Check for memory allocation failure
    if (!result.encrypted_data || !result.iv || !result.key) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        return result;
    }

    // Generate a secure random IV
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        return result;
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);

    // Copy the key and set the encryption key
    memcpy(result.key, key, key_len);
    if (AES_set_encrypt_key(result.key, 128, &aes_key) < 0) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        return result;
    }

    // Perform encryption in CBC mode
    AES_cbc_encrypt(data, result.encrypted_data, result.encrypted_len, &aes_key, result.iv, AES_ENCRYPT);

    return result;
}

// Remember to free the allocated memory for result.encrypted_data, result.iv, and result.key when done.