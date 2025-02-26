
/**
 * Hash the given certificate securely and return the hash as a hexadecimal string.
 *
 * @param {string} cert - The certificate to be hashed.
 * @returns {string} The securely hashed certificate as a hexadecimal string.
 */
function hash_certificate(cert) {
    const crypto = require('crypto');

    // Validate input
    if (typeof cert !== 'string' || cert.trim() === '') {
        throw new Error('Invalid certificate input');
    }

    // Use a secure hashing algorithm (SHA-256)
    const hash = crypto.createHash('sha256');
    hash.update(cert);

    // Return the hash as a hexadecimal string
    return hash.digest('hex');
}