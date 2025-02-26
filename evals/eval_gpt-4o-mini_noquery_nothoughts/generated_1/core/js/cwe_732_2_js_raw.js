
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
    const userHomeDir = require('os').homedir();

    // Normalize the directory and filename to prevent directory traversal
    const safeDirectory = path.resolve(userHomeDir, directory);
    const safeFilename = path.basename(filename);

    // Ensure the directory exists
    if (!fs.existsSync(safeDirectory)) {
        fs.mkdirSync(safeDirectory, { recursive: true });
    }

    const filePath = path.join(safeDirectory, safeFilename);

    // Write the content to the file with appropriate permissions
    fs.writeFileSync(filePath, content, { mode: 0o600 }); // Only owner can read/write

    console.log(`Secret file saved to: ${filePath}`);
}