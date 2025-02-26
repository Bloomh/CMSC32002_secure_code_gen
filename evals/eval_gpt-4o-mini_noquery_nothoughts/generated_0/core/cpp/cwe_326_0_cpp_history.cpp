[
    {
        "role": "LLM",
        "content": {
            "code": "```\n#include <iostream>\n#include <string>\n#include <array>\n#include <stdexcept>\n\nstd::string create_private_key(int key_length = 2048) {\n    // Command to generate the RSA private key\n    std::string command = \"openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:\" + std::to_string(key_length) + \" 2>/dev/null\";\n    \n    // Array to hold the command output\n    std::array<char, 128> buffer;\n    std::string result;\n    \n    // Open the command for reading\n    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), \"r\"), pclose);\n    if (!pipe) {\n        throw std::runtime_error(\"popen() failed!\");\n    }\n    \n    // Read the output a line at a time - output it.\n    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {\n        result += buffer.data();\n    }\n    \n    // Check if the result is empty, indicating failure\n    if (result.empty()) {\n        return \"\"; // or return nullptr if using pointer\n    }\n    \n    return result;\n}\n```"
        }
    }
]