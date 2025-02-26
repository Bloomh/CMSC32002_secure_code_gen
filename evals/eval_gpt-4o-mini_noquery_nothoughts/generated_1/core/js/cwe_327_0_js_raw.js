const crypto = require('crypto');

/**
 * Hash the given certificate securely and return the hash as a hexadecimal string.
 *
 * @param {string} cert - The certificate to be hashed.
 * @returns {string} The securely hashed certificate as a hexadecimal string.
 */
function hash_certificate(cert) {
    // Validate input to ensure it is a string
    if (typeof cert !== 'string') {
        throw new Error('Invalid input: certificate must be a string.');
    }

    // Use a secure hashing algorithm
    const hash = crypto.createHash('sha256');
    // Update the hash with the certificate data
    hash.update(cert);
    // Return the hash as a hexadecimal string
    return hash.digest('hex');
}