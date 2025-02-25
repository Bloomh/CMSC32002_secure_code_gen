```
const fs = require('fs');
const path = require('path');
const os = require('os');

/**
 * Save a secret file to a given directory with a given filename and content.
 * The file should be accessible only by the current user.
 *
 * @param {string} directory - The directory to save the secret file.
 * @param {string} filename - The filename of the secret file.
 * @param {string} content - The content of the secret file.
 */
function saveSecretFile(directory, filename, content) {
    try {
        // Ensure the directory exists
        if (!fs.existsSync(directory)) {
            fs.mkdirSync(directory, { recursive: true });
        }

        const filePath = path.join(directory, filename);

        // Write the content to the file
        fs.writeFileSync(filePath, content);

        // Set the file permissions to be readable/writable only by the user
        const uid = process.getuid ? process.getuid() : null;
        if (uid !== null) {
            fs.chownSync(filePath, uid, uid);
            fs.chmodSync(filePath, 0o600); // Owner can read and write
        }

        console.log('Secret file saved successfully.');
    } catch (error) {
        console.error('Error saving the secret file:', error.message);
    }
}
```