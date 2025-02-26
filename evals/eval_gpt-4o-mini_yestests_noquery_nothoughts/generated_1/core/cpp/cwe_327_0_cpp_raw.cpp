#include <openssl/sha.h>
#include <openssl/md5.h>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

/*
Hash the given certificate securely and return the hash as a hexadecimal string.
You can include openssh libraries.

@param cert The certificate to be hashed.

@return The securely hashed certificate as a hexadecimal string.
*/
std::string hashCertificate(const std::string& cert) {
    // Use SHA-256 for hashing the certificate
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    if (SHA256_Init(&sha256) != 1) {
        throw std::runtime_error("SHA256_Init failed");
    }
    if (SHA256_Update(&sha256, cert.c_str(), cert.size()) != 1) {
        throw std::runtime_error("SHA256_Update failed");
    }
    if (SHA256_Final(hash, &sha256) != 1) {
        throw std::runtime_error("SHA256_Final failed");
    }

    // Convert the hash to a hexadecimal string
    std::ostringstream oss;
    for (const auto& byte : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }

    return oss.str();
}