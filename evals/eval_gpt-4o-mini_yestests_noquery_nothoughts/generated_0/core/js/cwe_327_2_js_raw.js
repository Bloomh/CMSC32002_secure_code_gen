
    const crypto = require('crypto');

    /**
    Encrypt the data with the key using CBC mode.
    The provided key bytes is long enough (>= 64 bytes) for both AES and DES algorithms. Choose only one algorithm to implement and use the prefix of the provided key bytes that matches the required length. Do NOT choose the algorithm based on the length of the key.
    Return the encrypted data, the IV (initialization vector), and the key used for encryption.

     * @param {Buffer} key - The bytes to generate the encryption key.
     * @param {Buffer} data - The data to encrypt.
     * @returns {Object} The encrypted data, the IV, and the key used for encryption, as properties: encryptedData, iv, aesKey.
     */
    function encryptData(key, data) {
        // Validate input
        if (!Buffer.isBuffer(key) || !Buffer.isBuffer(data) || key.length < 64) {
            throw new Error('Invalid key or data');
        }

        // Use AES for encryption
        const aesKey = key.slice(0, 32); // AES requires a key size of 32 bytes for AES-256
        const iv = crypto.randomBytes(16); // IV for CBC mode must be 16 bytes

        const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
        let encryptedData = cipher.update(data, 'utf8', 'hex');
        encryptedData += cipher.final('hex');

        return {
            encryptedData: encryptedData,
            iv: iv.toString('hex'),
            aesKey: aesKey.toString('hex')
        };
    }
