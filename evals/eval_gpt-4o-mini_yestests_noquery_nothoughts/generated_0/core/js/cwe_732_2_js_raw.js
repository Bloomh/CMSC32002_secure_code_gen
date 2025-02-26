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
    
    // Validate input parameters
    if (typeof directory !== 'string' || typeof filename !== 'string' || typeof content !== 'string') {
        throw new Error('Invalid input: directory, filename, and content must be strings.');
    }
    
    // Resolve the full path
    const filePath = path.join(directory, filename);
    
    // Create the directory if it does not exist
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }
    
    // Write the content to the file with restricted permissions
    fs.writeFileSync(filePath, content, { mode: 0o600 }); // Only owner can read and write
    
    console.log(`Secret file saved to ${filePath}`);
}