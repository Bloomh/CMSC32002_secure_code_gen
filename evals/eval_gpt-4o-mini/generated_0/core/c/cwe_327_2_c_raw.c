#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

    // AES requires a key of 16, 24, or 32 bytes
    unsigned char aes_key[32]; // Maximum key size for AES
    memset(aes_key, 0, sizeof(aes_key));
    size_t key_size = (key_len < sizeof(aes_key)) ? key_len : sizeof(aes_key);
    memcpy(aes_key, key, key_size);

    // Generate a random IV
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!result.iv || !RAND_bytes(result.iv, AES_BLOCK_SIZE)) {
        fprintf(stderr, "Error generating IV\n");
        goto cleanup;
    }

    // Calculate the required length for the encrypted data (including padding)
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        fprintf(stderr, "Error allocating memory for encrypted data\n");
        goto cleanup;
    }

    // Initialize AES encryption
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(aes_key, 256, &encrypt_key) != 0) {
        fprintf(stderr, "Error setting AES encryption key\n");
        goto cleanup;
    }

    // Allocate memory for padded data
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        fprintf(stderr, "Error allocating memory for padded data\n");
        goto cleanup;
    }
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len); // Zero padding

    // Perform AES encryption in CBC mode
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &encrypt_key, result.iv, AES_ENCRYPT);
    result.encrypted_len = padded_len;

    // Set the key used for encryption
    result.key = (unsigned char*)malloc(sizeof(aes_key));
    if (!result.key) {
        fprintf(stderr, "Error allocating memory for key\n");
        goto cleanup;
    }
    memcpy(result.key, aes_key, sizeof(aes_key));

    free(padded_data);
    return result;

cleanup:
    free(result.encrypted_data);
    free(result.iv);
    free(result.key);
    free(padded_data);
    return result;
}