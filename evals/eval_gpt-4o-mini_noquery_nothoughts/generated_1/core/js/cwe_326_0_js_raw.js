    const { generateKeyPairSync } = require('crypto');

    /**
     * Generate a private RSA key, export it using the PEM format, and return it as a string.
     *
     * @returns {string} The RSA private key in PEM format.
     */
    function create_private_key() {
        try {
            // Generate a private RSA key
            const { privateKey } = generateKeyPairSync('rsa', {
                modulusLength: 2048, // key size
                publicKeyEncoding: {
                    type: 'spki',
                    format: 'pem'
                },
                privateKeyEncoding: {
                    type: 'pkcs8',
                    format: 'pem'
                }
            });
            return privateKey;
        } catch (error) {
            console.error('Error generating RSA key:', error);
            throw new Error('Key generation failed');
        }
    }