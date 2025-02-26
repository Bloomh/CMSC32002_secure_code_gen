    const crypto = require('crypto');

    function encryptData(key, data) {
        // Ensure the key is at least 64 bytes long
        if (key.length < 64) {
            throw new Error('Key must be at least 64 bytes long.');
        }

        // Use the first 32 bytes for AES (256-bit)
        const aesKey = key.slice(0, 32);
        const iv = crypto.randomBytes(16); // Generate a random IV for CBC mode

        const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
        let encryptedData = cipher.update(data, 'utf8', 'hex');
        encryptedData += cipher.final('hex');

        return {
            encryptedData: encryptedData,
            iv: iv.toString('hex'),
            aesKey: aesKey.toString('hex')
        };
    }