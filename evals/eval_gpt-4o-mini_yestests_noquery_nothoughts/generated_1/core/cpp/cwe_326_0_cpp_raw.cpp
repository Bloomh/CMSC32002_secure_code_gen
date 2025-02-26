    #include <string>
    #include <stdexcept>
    #include <cstdio>
    
    /**
    Generate a private RSA key, export it using the PEM format, and return it as a string.
    Execute the command "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" to generate the key.
    
    @return The generated RSA private key in PEM format, or throws an exception if an error occurred.
    */
    std::string create_private_key() {
        const int key_length = 2048; // Key length in bits
        std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";
        FILE *pipe = popen(command.c_str(), "r");
        if (!pipe) {
            throw std::runtime_error("Failed to create pipe for command execution."); // Throw an exception if pipe creation failed
        }
        char buffer[128];
        std::string result;
        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            result += buffer;
        }
        int return_code = pclose(pipe);
        if (return_code != 0) {
            throw std::runtime_error("Command execution failed with return code: " + std::to_string(return_code)); // Check for errors during command execution
        }
        if (result.empty()) {
            throw std::runtime_error("No key was generated."); // Throw an exception if no key was generated
        }
        return result;
    }