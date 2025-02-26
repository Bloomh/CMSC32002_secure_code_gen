[
    {
        "role": "LLM",
        "content": {
            "code": "const crypto = require('crypto');\n\n/**\nGiven a list of passwords of users, use pbkdf2Sync to hash them with SHA-256, salts of the same length as the output hash, and 10000 iterations. Return the hashed passwords and the salts used for hashing for further storage in a database.\n\n@param {string[]} usernames - An array of usernames.\n@param {string[]} passwords - An array of passwords of the users to hash.\n@return {Array<[Buffer, Buffer]>} An array of tuples containing the hashed passwords and the salts used for hashing.\n*/\nfunction hashPasswords(usernames, passwords) {\n    const iterations = 10000;\n    const hashLength = 32; // SHA-256 produces a 32-byte hash\n    const results = [];\n\n    for (let i = 0; i < usernames.length; i++) {\n        const password = passwords[i];\n        const salt = crypto.randomBytes(hashLength);\n        const hashedPassword = crypto.pbkdf2Sync(password, salt, iterations, hashLength, 'sha256');\n        results.push([hashedPassword, salt]);\n    }\n\n    return results;\n}"
        }
    }
]