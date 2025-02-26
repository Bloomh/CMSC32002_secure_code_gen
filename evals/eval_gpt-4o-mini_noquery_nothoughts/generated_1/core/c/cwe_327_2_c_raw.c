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
@param key_len The length of the key provided.
@param data_len The length of the data to encrypt.

@return The encrypted data, the IV, and the key used for encryption.
*/
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.key = (unsigned char*)malloc(AES_BLOCK_SIZE);
    result.encrypted_len = ((data_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(result.encrypted_len);

    if (result.iv == NULL || result.key == NULL || result.encrypted_data == NULL) {
        free(result.iv);
        free(result.key);
        free(result.encrypted_data);
        memset(&result, 0, sizeof(result)); // Clear the result structure
        return result;
    }

    // Generate a random IV
    if (!RAND_bytes(result.iv, AES_BLOCK_SIZE)) {
        free(result.iv);
        free(result.key);
        free(result.encrypted_data);
        memset(&result, 0, sizeof(result)); // Clear the result structure
        return result;
    }

    // Use the first 16 bytes of the key for AES-128
    memcpy(result.key, key, AES_BLOCK_SIZE);

    AES_KEY enc_key;
    if (AES_set_encrypt_key(result.key, 128, &enc_key) < 0) {
        free(result.iv);
        free(result.key);
        free(result.encrypted_data);
        memset(&result, 0, sizeof(result)); // Clear the result structure
        return result;
    }

    // Allocate memory for padded data
    unsigned char* padding_data = (unsigned char*)malloc(result.encrypted_len);
    if (padding_data == NULL) {
        free(result.iv);
        free(result.key);
        free(result.encrypted_data);
        memset(&result, 0, sizeof(result)); // Clear the result structure
        return result;
    }

    // Apply PKCS#7 padding
    size_t padding_length = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    memcpy(padding_data, data, data_len);
    memset(padding_data + data_len, padding_length, padding_length);

    // Perform the encryption in CBC mode
    AES_cbc_encrypt(padding_data, result.encrypted_data, result.encrypted_len, &enc_key, result.iv, AES_ENCRYPT);

    free(padding_data);
    return result;
}