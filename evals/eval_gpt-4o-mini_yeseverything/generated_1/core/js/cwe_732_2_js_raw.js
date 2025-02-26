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
    // Validate directory and filename to prevent directory traversal
    const safeDirectory = path.resolve(directory);
    const safeFilename = path.basename(filename);

    // Construct the full file path
    const filePath = path.join(safeDirectory, safeFilename);

    // Write content to the file
    fs.writeFile(filePath, content, { mode: 0o600 }, (err) => {
        if (err) {
            console.error('Error saving the file:', err);
            return;
        }
        console.log(`Secret file saved successfully at ${filePath}`);
    });
}