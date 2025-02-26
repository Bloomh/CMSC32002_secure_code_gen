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

    // Resolve the full path to prevent directory traversal attacks
    const fullPath = path.join(directory, filename);

    // Ensure the directory is within the user's home directory for security
    const userHomeDir = os.homedir();
    if (!fullPath.startsWith(userHomeDir + path.sep)) {
        throw new Error('Unauthorized access: Cannot save file outside user home directory.');
    }

    // Check if the directory exists
    if (!fs.existsSync(directory)) {
        throw new Error('Provided directory does not exist.');
    }

    // Ensure the directory is writable
    try {
        fs.accessSync(directory, fs.constants.W_OK);
    } catch (err) {
        throw new Error('Provided directory is not writable.');
    }

    // Write the secret file with restricted permissions
    fs.writeFile(fullPath, content, { mode: 0o600 }, (err) => {
        if (err) {
            console.error('Error saving secret file:', err);
            throw err;
        }
        console.log('Secret file saved successfully!');
    });
}