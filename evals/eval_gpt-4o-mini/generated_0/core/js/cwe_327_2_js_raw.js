const crypto = require('crypto');

/**
 * Encrypt the data with the key using CBC mode.
 * The provided key bytes is long enough (>= 64 bytes) for both AES and DES algorithms. Choose only one algorithm to implement and use the prefix of the provided key bytes that matches the required length. Do NOT choose the algorithm based on the length of the key.
 * Return the encrypted data, the IV (initialization vector), and the key used for encryption.
 *
 * @param {Buffer} key - The bytes to generate the encryption key.
 * @param {Buffer} data - The data to encrypt.
 * @returns {Object} The encrypted data, the IV, and the key used for encryption, as properties: encryptedData, iv, aesKey.
 */
function encryptData(key, data) {
    // Validate input types
    if (!Buffer.isBuffer(key) || !Buffer.isBuffer(data)) {
        throw new TypeError('Both key and data must be Buffer instances.');
    }

    // Define the AES key length (using 32 bytes for AES-256)
    const aesKeyLength = 32;
    const aesKey = key.slice(0, aesKeyLength);

    // Generate a random IV
    const iv = crypto.randomBytes(16);

    // Create the cipher
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);

    // Encrypt the data
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);

    // Return the encrypted data, IV, and key used for encryption
    return {
        encryptedData,
        iv,
        aesKey
    };
}