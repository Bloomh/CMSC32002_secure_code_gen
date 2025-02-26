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

    // Ensure the directory path is safe and resolves to an absolute path
    const safeDirPath = path.resolve(dir_path);
    const safeFilePath = path.join(safeDirPath, filename);

    // Check if the file is within the allowed directory
    if (!safeFilePath.startsWith(safeDirPath)) {
        return '';
    }

    try {
        return fs.readFileSync(safeFilePath, 'utf8');
    } catch (error) {
        return '';
    }
}