```
#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>
#include <cstdio>
#include <array>

std::string create_private_key(int key_length = 2048) {
    // Validate the key length
    if (key_length < 2048 || key_length > 4096) {
        throw std::invalid_argument("Key length must be between 2048 and 4096 bits.");
    }
    
    // Prepare the command to execute
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // Create a buffer to capture the output
    std::array<char, 128> buffer;
    std::string result;
    
    // Use a pipe to execute the command and read its output
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    
    // Read the output from the command
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