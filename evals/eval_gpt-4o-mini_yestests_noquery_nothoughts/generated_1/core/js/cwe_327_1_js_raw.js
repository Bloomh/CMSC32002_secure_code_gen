    const crypto = require('crypto');

    /**
     * Hash the given password securely and return the hash as a string.
     *
     * @param {string} password - The password to be hashed.
     * @returns {Promise<string>} The securely hashed password.
     */
    async function get_password_hash(password) {
        // Generate a secure salt
        const salt = crypto.randomBytes(16).toString('hex');

        return new Promise((resolve, reject) => {
            // Use PBKDF2 with a high iteration count and a secure hash algorithm
            crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
                if (err) {
                    return reject(err);
                }
                // Return the salt and hash in a format suitable for storage
                resolve(`${salt}:${derivedKey.toString('hex')}`);
            });
        });
    }