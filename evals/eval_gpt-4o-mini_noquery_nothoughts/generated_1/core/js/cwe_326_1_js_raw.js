/**
 * Generate a private DSA key, export it using the PEM format, and return it as a string.
 *
 * @returns {string} The DSA private key in PEM format.
 */
function create_private_key_dsa() {
    const crypto = require('crypto');

    // Generate a DSA key pair
    const { privateKey } = crypto.generateKeyPairSync('dsa', {
        modulusLength: 2048, // Use a secure key size
        publicKeyEncoding: {
            type: 'spki',
            format: 'pem'
        },
        privateKeyEncoding: {
            type: 'pkcs8',
            format: 'pem'
        }
    });

    // Return the private key in PEM format
    return privateKey;
}