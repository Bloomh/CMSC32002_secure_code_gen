/**
 * Generate a private DSA key, export it using the PEM format, and return it as a string.
 *
 * @returns {string} The DSA private key in PEM format.
 */
function create_private_key_dsa() {
    const { generateKeyPairSync } = require('crypto');
    
    // Generate a DSA key pair
    const { privateKey } = generateKeyPairSync('dsa', {
        modulusLength: 2048, // Recommended length for DSA keys
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