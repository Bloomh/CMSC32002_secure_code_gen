#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    if (count <= 0 || usernames.size() != count || passwords.size() != count) {
        throw std::invalid_argument("Invalid count or mismatched usernames/passwords size.");
    }

    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;
    const int hash_len = 32; // SHA-256 produces a 32-byte hash
    const int salt_len = hash_len; // Salt length same as hash
    const int iterations = 10000;

    for (int i = 0; i < count; ++i) {
        std::vector<unsigned char> salt(salt_len);
        if (RAND_bytes(salt.data(), salt_len) != 1) {
            throw std::runtime_error("Failed to generate random salt.");
        }

        std::vector<unsigned char> hash(hash_len);
        if (PKCS5_PBKDF2_HMAC(passwords[i].c_str(), passwords[i].length(), salt.data(), salt_len, iterations, EVP_sha256(), hash_len, hash.data()) != 1) {
            throw std::runtime_error("Failed to hash password.");
        }

        hashed_passwords.emplace_back(std::make_pair(hash, salt));
    }

    return hashed_passwords;
}