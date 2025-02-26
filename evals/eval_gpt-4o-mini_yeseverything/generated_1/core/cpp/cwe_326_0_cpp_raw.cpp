#include <iostream>
#include <string>
#include <stdexcept>
#include <array>
#include <memory>
#include <cstdio>

/**
 * Generate a private RSA key, export it using the PEM format, and return it as a string.
 * Execute the command "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" to generate the key.
 *
 * @return The generated RSA private key in PEM format.
 */
std::string create_private_key(int key_length = 2048) {
    // Check for valid key length
    if (key_length < 2048) {
        throw std::invalid_argument("Key length must be at least 2048 bits.");
    }

    // Prepare the command to generate RSA private key
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // Use a pipe to read the output of the command
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    // Read the output
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Check if the result is empty, indicating an error occurred
    if (result.empty()) {
        throw std::runtime_error("Failed to generate the private key.");
    }

    return result;
}

int main() {
    try {
        std::string private_key = create_private_key();
        std::cout << "Generated Private Key:\n" << private_key << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}