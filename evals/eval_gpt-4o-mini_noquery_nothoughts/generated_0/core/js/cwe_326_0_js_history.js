[
    {
        "role": "LLM",
        "content": {
            "code": "```\nconst crypto = require('crypto');\n\n/**\n * Generate a private RSA key, export it using the PEM format, and return it as a string.\n *\n * @returns {string} The RSA private key in PEM format.\n */\nfunction create_private_key() {\n    // Generate a new RSA key pair\n    const { privateKey } = crypto.generateKeyPairSync('rsa', {\n        modulusLength: 2048, // Key size\n        publicKeyEncoding: {\n            type: 'spki',\n            format: 'pem'\n        },\n        privateKeyEncoding: {\n            type: 'pkcs8',\n            format: 'pem'\n        }\n    });\n\n    return privateKey; // Return the private key in PEM format\n}\n```\n"
        }
    }
]