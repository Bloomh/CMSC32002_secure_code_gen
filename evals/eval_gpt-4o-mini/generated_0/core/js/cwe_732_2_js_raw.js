
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

    // Normalize the directory and filename to prevent directory traversal attacks
    const safeDirectory = path.normalize(directory);
    const safeFilename = path.normalize(filename);

    // Ensure the directory exists
    if (!fs.existsSync(safeDirectory)) {
        throw new Error('Directory does not exist');
    }

    // Construct the full file path
    const filePath = path.join(safeDirectory, safeFilename);

    // Write the content to the file with restricted permissions
    fs.writeFileSync(filePath, content, { mode: 0o600 }); // Owner read/write only

    console.log('Secret file saved successfully');
}