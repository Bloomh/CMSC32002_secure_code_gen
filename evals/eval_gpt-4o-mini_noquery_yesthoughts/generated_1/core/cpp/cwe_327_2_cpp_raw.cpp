#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>

// Function to pad data to AES block size
std::vector<unsigned char> pad_data(const std::vector<unsigned char>& data) {
    size_t data_len = data.size();
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_len = data_len + padding;

    std::vector<unsigned char> padded_data(data.begin(), data.end());
    padded_data.resize(padded_len, (unsigned char)padding);

    return padded_data;
}

typedef struct {
    std::vector<unsigned char> encrypted_data;
    std::vector<unsigned char> iv;
    std::vector<unsigned char> key;
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
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    encryption_result result;

    // Ensure the key is at least 16 bytes for AES-128
    if (key.size() < 16) {
        throw std::invalid_argument("Key must be at least 16 bytes long.");
    }

    // Generate a random IV
    result.iv.resize(AES_BLOCK_SIZE);
    if (RAND_bytes(result.iv.data(), result.iv.size()) != 1) {
        throw std::runtime_error("Failed to generate random IV.");
    }

    // Prepare AES key
    std::vector<unsigned char> aes_key(key.begin(), key.begin() + 16);

    // Pad data
    std::vector<unsigned char> padded_data = pad_data(data);

    // Setup AES context
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(aes_key.data(), 128, &encrypt_key) < 0) {
        throw std::runtime_error("Failed to set AES encryption key.");
    }

    // Encrypt data
    result.encrypted_data.resize(padded_data.size());
    unsigned char iv[AES_BLOCK_SIZE];
    memcpy(iv, result.iv.data(), AES_BLOCK_SIZE);

    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(padded_data.data() + i, result.encrypted_data.data() + i, AES_BLOCK_SIZE, &encrypt_key, iv, AES_ENCRYPT);
    }

    // Store the key used for encryption
    result.key = aes_key;

    return result;
}