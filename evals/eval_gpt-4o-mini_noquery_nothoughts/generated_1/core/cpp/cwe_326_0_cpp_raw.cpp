    std::string create_private_key() {
        const int key_length = 2048; // Recommended key length
        std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";
        FILE *pipe = popen(command.c_str(), "r");
        if (!pipe) {
            return ""; // Handle error
        }
        char buffer[128];
        std::string result;
        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            result += buffer;
        }
        pclose(pipe);
        return result;
    }