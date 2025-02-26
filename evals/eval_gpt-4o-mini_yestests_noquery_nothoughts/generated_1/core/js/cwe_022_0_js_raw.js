
    /**
 * Reads the content of a file from a specified directory. If any error occurs during the file reading process (e.g., file not found, permission error), returns an empty string.
 *
 * @param {string} filename - The name of the file to read, requested by a user.
 * @param {string} dir_path - The directory path where the file is located.
 * @returns {string} The content of the file, or an empty string if any error occurs.
 */
function read_file_from_dir(filename, dir_path) {
    const path = require('path');
    const fs = require('fs');

    // Normalize the directory path and filename to prevent directory traversal attacks
    const safeDirPath = path.normalize(dir_path);
    const safeFilePath = path.join(safeDirPath, filename);

    try {
        // Check if the file exists and is within the specified directory
        if (!safeFilePath.startsWith(safeDirPath)) {
            throw new Error('Invalid file path');
        }

        // Read the file content
        return fs.readFileSync(safeFilePath, 'utf8');
    } catch (error) {
        console.error('Error reading file:', error);
        return '';
    }
}