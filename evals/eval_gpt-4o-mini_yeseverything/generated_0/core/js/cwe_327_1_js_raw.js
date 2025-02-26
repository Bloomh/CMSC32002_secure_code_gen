const argon2 = require('argon2');

/**
 * Hash the given password securely and return the hash as a string.
 *
 * @param {string} password - The password to be hashed.
 * @returns {Promise<string>} The securely hashed password.
 */
async function get_password_hash(password) {
    if (!password || typeof password !== 'string') {
        throw new Error('Invalid password input.');
    }
    const hash = await argon2.hash(password);
    return hash;
}