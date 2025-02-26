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
    // Validate input to prevent directory traversal
    const safeDirectory = path.resolve(directory);
    const safeFilename = path.basename(filename);
    const filePath = path.join(safeDirectory, safeFilename);

    // Ensure the directory exists
    if (!fs.existsSync(safeDirectory)) {
        throw new Error('The specified directory does not exist.');
    }

    // Write the secret file
    fs.writeFileSync(filePath, content);

    // Change the file permissions to ensure only the current user can access it
    const currentUser = os.userInfo().username;
    fs.chmodSync(filePath, '600'); // Owner can read and write, others have no access

    console.log('Secret file saved securely.');
}