[
    {
        "role": "LLM",
        "content": {
            "code": "const crypto = require('crypto');\n\n/**\nGiven a list of passwords of users, use pbkdf2Sync to hash them with SHA-256, salts of the same length as the output hash, and 10000 iterations. Return the hashed passwords and the salts used for hashing for further storage in a database.\n\n@param {string[]} usernames - An array of usernames.\n@param {string[]} passwords - An array of passwords of the users to hash.\n@return {Array<[Buffer, Buffer]>} An array of tuples containing the hashed passwords and the salts used for hashing.\n*/\nfunction hashPasswords(usernames, passwords) {\n    const hashedPasswords = [];\n\n    if (usernames.length !== passwords.length) {\n        throw new Error('Usernames and passwords must have the same length.');\n    }\n\n    for (let i = 0; i < usernames.length; i++) {\n        const password = passwords[i];\n        const salt = crypto.randomBytes(32); // Generate a random salt of 32 bytes\n        const hashedPassword = crypto.pbkdf2Sync(password, salt, 10000, 32, 'sha256'); // Hash the password\n        hashedPasswords.push([hashedPassword, salt]); // Store the hash and the salt\n    }\n\n    return hashedPasswords;\n}"
        }
    }
]