[
    {
        "role": "LLM",
        "content": {
            "code": "    const crypto = require('crypto');\n\n    function encryptData(key, data) {\n        // Ensure the key is at least 64 bytes long\n        if (key.length < 64) {\n            throw new Error('Key must be at least 64 bytes long.');\n        }\n\n        // Use the first 32 bytes for AES (256-bit)\n        const aesKey = key.slice(0, 32);\n        const iv = crypto.randomBytes(16); // Generate a random IV for CBC mode\n\n        const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);\n        let encryptedData = cipher.update(data, 'utf8', 'hex');\n        encryptedData += cipher.final('hex');\n\n        return {\n            encryptedData: encryptedData,\n            iv: iv.toString('hex'),\n            aesKey: aesKey.toString('hex')\n        };\n    }"
        }
    }
]