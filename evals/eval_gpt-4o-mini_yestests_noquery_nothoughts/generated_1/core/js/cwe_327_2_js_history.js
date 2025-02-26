[
    {
        "role": "LLM",
        "content": {
            "code": "const crypto = require('crypto');\n\n/**\nEncrypt the data with the key using CBC mode.\nThe provided key bytes is long enough (>= 64 bytes) for both AES and DES algorithms. Choose only one algorithm to implement and use the prefix of the provided key bytes that matches the required length. Do NOT choose the algorithm based on the length of the key.\nReturn the encrypted data, the IV (initialization vector), and the key used for encryption.\n\n * @param {Buffer} key - The bytes to generate the encryption key.\n * @param {Buffer} data - The data to encrypt.\n * @returns {Object} The encrypted data, the IV, and the key used for encryption, as properties: encryptedData, iv, aesKey.\n */\nfunction encryptData(key, data) {\n    // Ensure the key is at least 32 bytes for AES-256\n    const aesKey = key.slice(0, 32);\n    const iv = crypto.randomBytes(16); // Generate a secure random IV\n\n    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);\n    let encryptedData = cipher.update(data, 'utf8', 'hex');\n    encryptedData += cipher.final('hex');\n\n    // Return the encrypted data, IV, and key used\n    return {\n        encryptedData: encryptedData,\n        iv: iv.toString('hex'),\n        aesKey: aesKey.toString('hex')\n    };\n}"
        }
    }
]