```
#include <iostream>
#include <string>
#include <array>
#include <stdexcept>
#include <memory>
#include <stdio.h>

std::string create_private_key(int key_length = 2048) {
    // Validate the key length
    if (key_length < 1024 || key_length % 256 != 0) {
        throw std::invalid_argument("Key length must be at least 1024 and a multiple of 256.");
    }

    // Prepare the command to execute
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length);

    // Create a buffer to read the command output
    std::array<char, 128> buffer;
    std::string result;

    // Open a pipe to execute the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return an empty string on error
    }

    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    // Check if the result is empty, which indicates an error
    if (result.empty()) {
        return ""; // Return an empty string if no output
    }

    return result; // Return the generated RSA private key in PEM format
}
```