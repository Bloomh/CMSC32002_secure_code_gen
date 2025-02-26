const crypto = require('crypto');

/**
Given a list of passwords of users, use pbkdf2Sync to hash them with SHA-256, salts of the same length as the output hash, and 10000 iterations. Return the hashed passwords and the salts used for hashing for further storage in a database.

@param {string[]} usernames - An array of usernames.
@param {string[]} passwords - An array of passwords of the users to hash.
@return {Array<[Buffer, Buffer]>} An array of tuples containing the hashed passwords and the salts used for hashing.
*/
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashLength = 32; // SHA-256 produces a 32-byte hash
    const results = [];

    for (let i = 0; i < passwords.length; i++) {
        const password = passwords[i];
        const salt = crypto.randomBytes(hashLength);
        const hashedPassword = crypto.pbkdf2Sync(password, salt, iterations, hashLength, 'sha256');
        results.push([hashedPassword, salt]);
    }

    return results;
}