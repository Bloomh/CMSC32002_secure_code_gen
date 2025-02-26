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
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = malloc(padded_len);

    // Check for memory allocation failure
    if (padded_data == NULL) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Padding the data
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len);  // Zero padding

    // Generate a random IV
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        free(padded_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Set the AES key (128 bits)
    if (AES_set_encrypt_key(key, 128, &aes_key) != 0) {
        free(padded_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Allocate memory for encrypted data
    result.encrypted_data = malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(padded_data);
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // Encrypting in CBC mode
    for (size_t i = 0; i < padded_len; i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(padded_data + i, result.encrypted_data + i, AES_BLOCK_SIZE, &aes_key, iv, AES_ENCRYPT);
    }

    // Populate the result structure
    result.encrypted_len = padded_len;
    result.iv = malloc(AES_BLOCK_SIZE);
    if (result.iv != NULL) {
        memcpy(result.iv, iv, AES_BLOCK_SIZE);
    }
    result.key = malloc(key_len);
    if (result.key != NULL) {
        memcpy(result.key, key, key_len);
    }

    // Cleanup
    free(padded_data);

    return result;
}