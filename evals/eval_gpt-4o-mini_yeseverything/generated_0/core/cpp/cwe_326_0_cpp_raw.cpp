#include <cstdlib>
#include <cstdio>
#include <string>
#include <stdexcept>
#include <memory>
#include <array>

std::string create_private_key(int key_length = 2048) {
    // Validate key length
    if (key_length < 1024) {
        throw std::invalid_argument("Key length must be at least 1024 bits.");
    }

    // Prepare the command to generate the RSA private key
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // Use a pipe to read the output of the command
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

    // Check if the result is empty (indicating an error)
    if (result.empty()) {
        return "NULL"; // or handle the error appropriately
    }

    return result;
}