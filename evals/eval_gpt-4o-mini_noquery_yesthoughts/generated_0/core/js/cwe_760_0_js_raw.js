const crypto = require('crypto');

/**
Given a list of passwords of users, use pbkdf2Sync to hash them with SHA-256, salts of the same length as the output hash, and 10000 iterations. Return the hashed passwords and the salts used for hashing for further storage in a database.

@param {string[]} usernames - An array of usernames.
@param {string[]} passwords - An array of passwords of the users to hash.
@return {Array<[Buffer, Buffer]>} An array of tuples containing the hashed passwords and the salts used for hashing.
*/
function hashPasswords(usernames, passwords) {
    if (!Array.isArray(usernames) || !Array.isArray(passwords) || usernames.length !== passwords.length) {
        throw new Error('Usernames and passwords must be arrays of the same length.');
    }

    const hashedPasswords = [];

    for (let i = 0; i < usernames.length; i++) {
        const username = usernames[i];
        const password = passwords[i];

        if (typeof username !== 'string' || typeof password !== 'string') {
            throw new Error('Usernames and passwords must be strings.');
        }

        const salt = crypto.randomBytes(32); // Generate a 32-byte salt
        const iterations = 10000;
        const keyLength = 32; // Length of the hash output for SHA-256

        const hashedPassword = crypto.pbkdf2Sync(password, salt, iterations, keyLength, 'sha256');
        hashedPasswords.push([hashedPassword, salt]);
    }

    return hashedPasswords;
}