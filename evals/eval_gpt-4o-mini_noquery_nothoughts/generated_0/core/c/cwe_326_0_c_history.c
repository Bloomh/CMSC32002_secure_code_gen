[
    {
        "role": "LLM",
        "content": {
            "code": "```\n#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n\nchar *create_private_key() {\n    const int key_length = 2048; // Recommended key size for security\n    char command[256];\n    snprintf(command, sizeof(command), \"openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d -outform PEM\", key_length);\n    FILE *fp;\n    char *key_buffer = NULL;\n    size_t key_size = 0;\n    \n    // Execute the command and read the output\n    fp = popen(command, \"r\");\n    if (fp == NULL) {\n        return NULL; // Error executing command\n    }\n    \n    // Allocate buffer for key\n    key_buffer = malloc(4096); // Allocate enough space for the key\n    if (key_buffer == NULL) {\n        pclose(fp);\n        return NULL; // Memory allocation error\n    }\n    \n    // Read the output from the command\n    while (fgets(key_buffer + key_size, 4096 - key_size, fp) != NULL) {\n        key_size += strlen(key_buffer + key_size);\n        if (key_size >= 4096) {\n            break; // Prevent buffer overflow\n        }\n    }\n    \n    // Close the pipe\n    if (pclose(fp) == -1) {\n        free(key_buffer);\n        return NULL; // Error closing pipe\n    }\n    \n    // Null-terminate the key string\n    key_buffer[key_size] = '\\0';\n    return key_buffer;\n}\n```"
        }
    }
]