
    const crypto = require('crypto');

    /**
 * Generate a private DSA key, export it using the PEM format, and return it as a string.
 *
 * @returns {string} The DSA private key in PEM format.
 */
function create_private_key_dsa() {
    try {
        // Generate a DSA key pair
        const { privateKey, publicKey } = crypto.generateKeyPairSync('dsa', {
            modulusLength: 2048, // DSA key size
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
    } catch (error) {
        console.error('Error generating DSA key:', error);
        throw new Error('Key generation failed'); // Rethrow with a generic error message
    }
}