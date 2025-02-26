
    /**
 * Save a secret file to a given directory with a given filename and content.
 * The file should be accessible only by the current user.
 *
 * @param {string} directory - The directory to save the secret file.
 * @param {string} filename - The filename of the secret file.
 * @param {string} content - The content of the secret file.
 */
function saveSecretFile(directory, filename, content) {
    const fs = require('fs');
    const path = require('path');
    const os = require('os');

    // Validate inputs
    if (typeof directory !== 'string' || typeof filename !== 'string' || typeof content !== 'string') {
        throw new Error('Invalid input types.');
    }

    // Resolve the full path
    const filePath = path.join(directory, filename);

    // Ensure the directory exists
    if (!fs.existsSync(directory)) {
        throw new Error('Directory does not exist.');
    }

    // Check if the directory is writable
    try {
        fs.accessSync(directory, fs.constants.W_OK);
    } catch (err) {
        throw new Error('Directory is not writable.');
    }

    // Write the content to the file with restricted permissions
    fs.writeFileSync(filePath, content, { mode: 0o600 }); // Owner can read/write only

    console.log('Secret file saved successfully.');
}