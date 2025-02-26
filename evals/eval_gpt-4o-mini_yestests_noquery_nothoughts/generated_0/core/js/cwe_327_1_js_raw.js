    const bcrypt = require('bcrypt');

    const saltRounds = 12; // Increased salt rounds for better security

    /**
     * Hash the given password securely and return the hash as a string.
     *
     * @param {string} password - The password to be hashed.
     * @returns {Promise<string>} The securely hashed password.
     */
    async function get_password_hash(password) {
        // Validate password input
        if (typeof password !== 'string' || password.length < 8) {
            throw new Error('Password must be a string with at least 8 characters.');
        }

        // Hash the password securely using bcrypt
        try {
            const hash = await bcrypt.hash(password, saltRounds);
            return hash;
        } catch (error) {
            throw new Error('Error hashing password: ' + error.message);
        }
    }
