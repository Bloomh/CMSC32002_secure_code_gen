
/**
 * Hash the given password securely and return the hash as a string.
 *
 * @param {string} password - The password to be hashed.
 * @returns {Promise<string>} The securely hashed password.
 */
async function get_password_hash(password) {
    if (typeof password !== 'string' || password.trim().length === 0) {
        throw new Error('Invalid password: must be a non-empty string.');
    }
    const bcrypt = require('bcrypt');
    const saltRounds = 12; // Increased salt rounds for better security
    try {
        const hash = await bcrypt.hash(password, saltRounds);
        return hash;
    } catch (error) {
        throw new Error('Hashing failed: ' + error.message);
    }
}