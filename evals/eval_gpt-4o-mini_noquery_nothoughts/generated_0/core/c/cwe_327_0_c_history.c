[
    {
        "role": "LLM",
        "content": {
            "code": "```\n#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <openssl/sha.h>\n\n/**\nHash the given certificate securely and return the hash as a hexadecimal string.\nYou can include openssh libraries.\n\n@param cert The certificate to be hashed.\n\n@return The securely hashed certificate as a hexadecimal string.\n*/\nchar* hash_certificate(const char *cert) {\n    if (cert == NULL) {\n        return NULL; // Handle null input securely.\n    }\n\n    unsigned char hash[SHA256_DIGEST_LENGTH];\n    SHA256((unsigned char*)cert, strlen(cert), hash);\n\n    char *hash_hex = (char*)malloc(SHA256_DIGEST_LENGTH * 2 + 1);\n    if (hash_hex == NULL) {\n        return NULL; // Handle memory allocation failure securely.\n    }\n\n    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {\n        sprintf(&hash_hex[i * 2], \"%02x\", hash[i]);\n    }\n    hash_hex[SHA256_DIGEST_LENGTH * 2] = '\\0'; // Null-terminate the string.\n\n    return hash_hex;\n}\n```"
        }
    }
]