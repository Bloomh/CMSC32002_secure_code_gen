#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>

/*
Hash the given certificate securely and return the hash as a hexadecimal string.
You can include openssl libraries.

@param cert The certificate to be hashed.

@return The securely hashed certificate as a hexadecimal string.
*/
std::string hashCertificate(const std::string& cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    if (SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash) == nullptr) {
        throw std::runtime_error("Hashing failed");
    }

    std::ostringstream hexStream;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return hexStream.str();
}