#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key(int key_length = 2048) {
    // Validate key length
    if (key_length < 512 || key_length > 4096 || key_length % 2 != 0) {
        throw std::invalid_argument("Key length must be an even number between 512 and 4096.");
    }
    
    // Prepare the command to generate the RSA private key
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length);
    
    // Use a pipe to read the output
    std::array<char, 128> buffer;
    std::string result;
    
    // Open a pipe to execute the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    
    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Check if the result is empty, which indicates an error
    if (result.empty()) {
        return ""; // or return NULL, depending on the desired return type
    }
    
    return result;
}