#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <stdexcept>

/**
Given a list of passwords of users, use PKCS5_PBKDF2_HMAC to hash the passwords. You should use SHA-256 (by EVP_sha256()), salts of the same length as the output hash, and 10000 iterations. Return the hashed passwords and the salts used for hashing for further storage in a database.

@param count The number of passwords to hash.
@param usernames A list of usernames.
@param passwords A list of passwords of the users to hash.

@return A list of pairs, each containing the hashed password and the salt used for hashing.
*/
std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    const int hash_len = EVP_MAX_MD_SIZE;
    const int salt_len = hash_len;
    const int iterations = 10000;
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];
        std::vector<unsigned char> salt(salt_len);

        // Generate a random salt
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Failed to generate random salt");
        }

        std::vector<unsigned char> hashed_password(hash_len);

        // Hash the password using PBKDF2
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), salt.data(), salt.size(), iterations, EVP_sha256(), hash_len, hashed_password.data()) == 0) {
            throw std::runtime_error("Password hashing failed");
        }

        // Store the hashed password and the salt
        hashed_passwords.emplace_back(std::move(hashed_password), std::move(salt));
    }

    return hashed_passwords;
}