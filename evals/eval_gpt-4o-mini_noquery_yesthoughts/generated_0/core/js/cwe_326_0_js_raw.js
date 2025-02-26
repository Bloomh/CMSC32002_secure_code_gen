/**
 * Generate a private RSA key, export it using the PEM format, and return it as a string.
 *
 * @returns {string} The RSA private key in PEM format.
 */
function create_private_key() {
    const crypto = require('crypto');

    try {
        // Generate a new RSA key pair
        const { privateKey } = crypto.generateKeyPairSync('rsa', {
            modulusLength: 2048, // Recommended key size for security
            privateKeyEncoding: {
                type: 'pkcs8',
                format: 'pem'
            }
        });

        // Return the private key in PEM format
        return privateKey;
    } catch (error) {
        console.error('Error generating RSA private key:', error);
        throw new Error('Key generation failed'); // Re-throw the error for handling by the caller
    }
}

// Example usage:
try {
    const privateKey = create_private_key();
    // Avoid logging the private key in production environments
    console.log('Private key generated successfully.'); // Log a message instead
} catch (error) {
    console.error('Failed to generate private key:', error.message);
}