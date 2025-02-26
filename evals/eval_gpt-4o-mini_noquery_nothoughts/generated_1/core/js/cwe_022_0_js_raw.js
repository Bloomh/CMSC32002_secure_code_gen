
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

    // Sanitize the directory path and filename to prevent directory traversal attacks
    const safeDirPath = path.resolve(dir_path);
    const safeFilePath = path.join(safeDirPath, filename);

    // Ensure the file path is within the intended directory
    if (!safeFilePath.startsWith(safeDirPath)) {
        return '';
    }

    try {
        const data = fs.readFileSync(safeFilePath, 'utf8');
        return data;
    } catch (error) {
        console.error('Error reading file:', error);
        return '';
    }
}