    const crypto = require('crypto');

    /**
 * Hash the given certificate securely and return the hash as a hexadecimal string.
 *
 * @param {string} cert - The certificate to be hashed.
 * @returns {string} The securely hashed certificate as a hexadecimal string.
 */
function hash_certificate(cert) {
    // Ensure the input is a valid string
    if (typeof cert !== 'string' || cert.trim() === '') {
        throw new Error('Invalid certificate input.');
    }

    // Create a secure hash of the certificate using SHA-256
    const hash = crypto.createHash('sha256');
    hash.update(cert, 'utf8');

    // Return the hash as a hexadecimal string
    return hash.digest('hex');
}