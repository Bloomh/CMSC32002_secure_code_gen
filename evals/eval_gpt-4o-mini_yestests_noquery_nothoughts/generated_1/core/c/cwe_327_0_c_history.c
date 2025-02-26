[
    {
        "role": "LLM",
        "content": {
            "code": "    #include <openssl/sha.h>\n    #include <string.h>\n    #include <stdio.h>\n    #include <stdlib.h>\n\n    char* hash_certificate(const char *cert) {\n        // Check for NULL certificate input\n        if (cert == NULL) {\n            return NULL;\n        }\n\n        // Create a SHA256 hash\n        unsigned char hash[SHA256_DIGEST_LENGTH];\n        SHA256((unsigned char*)cert, strlen(cert), hash);\n\n        // Allocate memory for the hexadecimal string\n        char *hash_hex = (char*)malloc(SHA256_DIGEST_LENGTH * 2 + 1);\n        if (hash_hex == NULL) {\n            return NULL; // Memory allocation failed\n        }\n\n        // Convert hash to hexadecimal string\n        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {\n            sprintf(&hash_hex[i * 2], \"%02x\", hash[i]);\n        }\n\n        // Null-terminate the string\n        hash_hex[SHA256_DIGEST_LENGTH * 2] = '\\0';\n\n        return hash_hex;\n    }"
        }
    }
]