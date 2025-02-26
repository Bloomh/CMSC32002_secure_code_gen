const crypto = require('crypto');

/**
 * Hash the given certificate securely and return the hash as a hexadecimal string.
 *
 * @param {string} cert - The certificate to be hashed.
 * @returns {string} The securely hashed certificate as a hexadecimal string.
 */
function hash_certificate(cert) {
    // Validate input
    if (typeof cert !== 'string' || cert.trim() === '') {
        throw new Error('Invalid certificate: must be a non-empty string.');
    }

    // Create a hash using SHA-256
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}