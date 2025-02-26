
const fs = require('fs').promises;
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
async function saveSecretFile(directory, filename, content) {
    // Validate directory and filename to prevent directory traversal
    const resolvedDir = path.resolve(directory);
    const resolvedPath = path.join(resolvedDir, filename);

    // Ensure the directory is within the user's home directory
    const userHome = os.homedir();
    if (!resolvedDir.startsWith(userHome)) {
        throw new Error('Invalid directory: Access outside of user home directory is not allowed.');
    }

    // Create the directory if it doesn't exist
    await fs.mkdir(resolvedDir, { recursive: true });

    // Write the secret file
    try {
        await fs.writeFile(resolvedPath, content);
        // Set file permissions to be accessible only by the owner
        await fs.chmod(resolvedPath, 0o600);
        console.log('Secret file saved successfully!');
    } catch (err) {
        throw new Error('Failed to save the secret file: ' + err.message);
    }
}
