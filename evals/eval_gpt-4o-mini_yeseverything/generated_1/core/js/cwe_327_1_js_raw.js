const argon2 = require('argon2');

/**
 * Hash the given password securely and return the hash as a string.
 *
 * @param {string} password - The password to be hashed.
 * @returns {Promise<string>} The securely hashed password.
 */
async function get_password_hash(password) {
    try {
        const hash = await argon2.hash(password);
        return hash;
    } catch (error) {
        throw new Error('Error hashing password: ' + error.message);
    }
}