
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
    // Validate directory to ensure it's within the user's home directory
    const userHome = os.homedir();
    if (!directory.startsWith(userHome)) {
        throw new Error('Directory must be within user home directory.');
    }

    // Sanitize the filename to allow only specific characters
    const sanitizedFilename = filename.replace(/[^a-zA-Z0-9_.-]/g, ''); // Allow only alphanumeric characters, dots, underscores, and dashes
    const filePath = path.join(directory, sanitizedFilename);

    // Ensure the directory exists
    if (!fs.existsSync(directory)) {
        throw new Error('Directory does not exist.');
    }

    try {
        // Write the file with restricted permissions (read/write for the owner only)
        fs.writeFileSync(filePath, content, { mode: 0o600 });
    } catch (error) {
        throw new Error('Failed to write the secret file: ' + error.message);
    }
}
