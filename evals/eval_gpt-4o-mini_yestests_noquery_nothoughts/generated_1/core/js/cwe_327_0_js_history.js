[
    {
        "role": "LLM",
        "content": {
            "code": "```\nconst crypto = require('crypto');\n\n/**\n * Hash the given certificate securely and return the hash as a hexadecimal string.\n *\n * @param {string} cert - The certificate to be hashed.\n * @returns {string} The securely hashed certificate as a hexadecimal string.\n */\nfunction hash_certificate(cert) {\n    // Validate the input to ensure it's a string\n    if (typeof cert !== 'string' || cert.trim() === '') {\n        throw new Error('Invalid input: certificate must be a non-empty string.');\n    }\n\n    // Create a secure hash using SHA-256\n    const hash = crypto.createHash('sha256');\n    hash.update(cert);\n\n    // Return the hash in hexadecimal format\n    return hash.digest('hex');\n}\n```"
        }
    }
]