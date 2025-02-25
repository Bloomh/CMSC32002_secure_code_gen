#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <string>

/*
Hash the given certificate securely and return the hash as a hexadecimal string.
You can include openssh libraries.

@param cert The certificate to be hashed.

@return The securely hashed certificate as a hexadecimal string.
*/
std::string hashCertificate(const std::string& cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    if (!SHA256_Init(&sha256)) {
        throw std::runtime_error("SHA256_Init failed");
    }
    if (!SHA256_Update(&sha256, cert.c_str(), cert.length())) {
        throw std::runtime_error("SHA256_Update failed");
    }
    if (!SHA256_Final(hash, &sha256)) {
        throw std::runtime_error("SHA256_Final failed");
    }
    std::ostringstream hexStream;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        hexStream << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(hash[i]);
    }
    return hexStream.str();
}