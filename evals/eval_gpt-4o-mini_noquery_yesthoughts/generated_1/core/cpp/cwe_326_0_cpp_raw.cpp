```
#include <iostream>
#include <string>
#include <stdexcept>
#include <array>
#include <memory>

std::string create_private_key(size_t key_length = 2048) {
    if (key_length < 2048) {
        throw std::invalid_argument("Key length must be at least 2048 bits.");
    }

    // Prepare the command to generate the RSA private key using OpenSSL
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // Use popen to execute the command and read the output
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    // Read the output of the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Check if the result is empty, indicating an error occurred
    if (result.empty()) {
        throw std::runtime_error("Failed to generate RSA private key.");
    }

    return result;
}
```