```
#include <iostream>
#include <string>
#include <array>
#include <stdexcept>

std::string create_private_key(int key_length = 2048) {
    // Command to generate the RSA private key
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";
    
    // Array to hold the command output
    std::array<char, 128> buffer;
    std::string result;
    
    // Open the command for reading
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    
    // Read the output a line at a time - output it.
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Check if the result is empty, indicating failure
    if (result.empty()) {
        return ""; // or return nullptr if using pointer
    }
    
    return result;
}
```