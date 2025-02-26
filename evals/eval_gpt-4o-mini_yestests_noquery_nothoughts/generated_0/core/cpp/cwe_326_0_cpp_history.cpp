[
    {
        "role": "LLM",
        "content": {
            "code": "```\n#include <iostream>\n#include <string>\n#include <stdexcept>\n#include <memory>\n#include <cstdio>\n#include <array>\n\nstd::string create_private_key(int key_length = 2048) {\n    // Validate the key length\n    if (key_length < 2048 || key_length > 4096) {\n        throw std::invalid_argument(\"Key length must be between 2048 and 4096 bits.\");\n    }\n    \n    // Prepare the command to execute\n    std::string command = \"openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:\" + std::to_string(key_length) + \" 2>/dev/null\";\n\n    // Create a buffer to capture the output\n    std::array<char, 128> buffer;\n    std::string result;\n    \n    // Use a pipe to execute the command and read its output\n    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), \"r\"), pclose);\n    if (!pipe) {\n        throw std::runtime_error(\"popen() failed!\");\n    }\n    \n    // Read the output from the command\n    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {\n        result += buffer.data();\n    }\n    \n    // Check if the result is empty, indicating an error occurred\n    if (result.empty()) {\n        throw std::runtime_error(\"Failed to generate RSA private key.\");\n    }\n    \n    return result;\n}\n```"
        }
    }
]