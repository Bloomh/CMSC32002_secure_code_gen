#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>

/**
Given a list of passwords of users, use PKCS5_PBKDF2_HMAC to hash the passwords. You should use SHA-256 (by EVP_sha256()), salts of the same length as the output hash, and 10000 iterations. Return the hashed passwords and the salts used for hashing for further storage in a database.

@param count The number of passwords to hash.
@param usernames A list of usernames.
@param passwords A list of passwords of the users to hash.

@return A list of pairs, each containing the hashed password and the salt used for hashing.
*/
std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    if (count <= 0 || count != usernames.size() || count != passwords.size()) {
        throw std::invalid_argument("Invalid input sizes.");
    }

    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;
    const int hash_length = EVP_MD_size(EVP_sha256());

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];

        // Generate a random salt
        std::vector<unsigned char> salt(hash_length);
        if (RAND_bytes(salt.data(), hash_length) != 1) {
            throw std::runtime_error("Failed to generate random salt.");
        }

        // Hash the password with the salt
        std::vector<unsigned char> hash(hash_length);
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), salt.data(), salt.size(), 10000, EVP_sha256(), hash_length, hash.data()) == 0) {
            throw std::runtime_error("Password hashing failed.");
        }

        hashed_passwords.emplace_back(hash, salt);
    }

    return hashed_passwords;
}