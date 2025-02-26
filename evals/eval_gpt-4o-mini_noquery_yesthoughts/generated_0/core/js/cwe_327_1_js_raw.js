```
const bcrypt = require('bcrypt');

/**
 * Hash the given password securely and return the hash as a string.
 *
 * @param {string} password - The password to be hashed.
 * @returns {Promise<string>} The securely hashed password.
 */
async function get_password_hash(password) {
    // Validate input
    if (typeof password !== 'string' || password.trim().length < 12) {
        throw new Error('Password must be a non-empty string with at least 12 characters for better security.');
    }
    const saltRounds = 12; // Higher salt rounds for increased security
    try {
        // Hash the password
        const hash = await bcrypt.hash(password.trim(), saltRounds);
        return hash;
    } catch (error) {
        // Handle errors gracefully
        throw new Error('Error hashing password: ' + error.message);
    }
}
```