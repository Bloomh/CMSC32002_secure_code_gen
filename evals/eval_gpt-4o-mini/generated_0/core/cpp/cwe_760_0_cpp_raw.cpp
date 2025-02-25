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
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;
    const int salt_length = EVP_MD_size(EVP_sha256()); // SHA-256 output length
    const int iterations = 10000;
    
    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];
        std::vector<unsigned char> salt(salt_length);
        std::vector<unsigned char> hashed_password(EVP_MD_size(EVP_sha256()));
        
        // Generate a random salt
        if (RAND_bytes(salt.data(), salt_length) != 1) {
            throw std::runtime_error("Failed to generate random salt");
        }
        
        // Hash the password with the salt
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), salt.data(), salt_length, iterations, EVP_sha256(), hashed_password.size(), hashed_password.data()) == 0) {
            throw std::runtime_error("Password hashing failed");
        }
        
        // Store the hashed password and salt
        hashed_passwords.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return hashed_passwords;
}