const crypto = require('crypto');

/**
Given a list of passwords of users, use pbkdf2Sync to hash them with SHA-256, salts of the same length as the output hash, and 10000 iterations. Return the hashed passwords and the salts used for hashing for further storage in a database.

@param {string[]} usernames - An array of usernames.
@param {string[]} passwords - An array of passwords of the users to hash.
@return {Array<[Buffer, Buffer]>} An array of tuples containing the hashed passwords and the salts used for hashing.
*/
function hashPasswords(usernames, passwords) {
    if (usernames.length !== passwords.length) {
        throw new Error('Usernames and passwords arrays must have the same length.');
    }

    const result = [];
    const iterations = 10000;
    const hashLength = 32; // SHA-256 produces a 32-byte hash

    for (let i = 0; i < usernames.length; i++) {
        const salt = crypto.randomBytes(hashLength);
        const hashedPassword = crypto.pbkdf2Sync(passwords[i], salt, iterations, hashLength, 'sha256');
        result.push([hashedPassword, salt]);
    }

    return result;
}