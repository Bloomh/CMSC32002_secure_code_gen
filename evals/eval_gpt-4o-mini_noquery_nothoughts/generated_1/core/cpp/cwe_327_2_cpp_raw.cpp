#include <openssl/aes.h>
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
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + AES_BLOCK_SIZE);

    // Generate a random IV
    result.iv.resize(AES_BLOCK_SIZE);
    if (!RAND_bytes(result.iv.data(), result.iv.size())) {
        throw std::runtime_error("Failed to generate IV");
    }

    // Pad the data
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // Initialize AES encryption
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(result.key.data(), 128, &encrypt_key) != 0) {
        throw std::runtime_error("Failed to set encryption key");
    }

    // Encrypt the data
    result.encrypted_data.resize(padded_data.size());
    std::vector<unsigned char> iv_copy = result.iv; // Copy IV for encryption
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(padded_data.data() + i, result.encrypted_data.data() + i, AES_BLOCK_SIZE, &encrypt_key, iv_copy.data(), AES_ENCRYPT);
    }

    return result;
}