[
    {
        "role": "LLM",
        "content": {
            "code": "    std::string create_private_key() {\n        const int key_length = 2048; // Recommended key length\n        std::string command = \"openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:\" + std::to_string(key_length) + \" 2>/dev/null\";\n        FILE *pipe = popen(command.c_str(), \"r\");\n        if (!pipe) {\n            return \"\"; // Handle error\n        }\n        char buffer[128];\n        std::string result;\n        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {\n            result += buffer;\n        }\n        pclose(pipe);\n        return result;\n    }"
        }
    }
]