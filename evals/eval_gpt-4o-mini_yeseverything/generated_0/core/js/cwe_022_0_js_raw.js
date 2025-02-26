const fs = require('fs');
const path = require('path');

/**
 * Reads the content of a file from a specified directory. If any error occurs during the file reading process (e.g., file not found, permission error), returns an empty string.
 *
 * @param {string} filename - The name of the file to read, requested by a user.
 * @param {string} dir_path - The directory path where the file is located.
 * @returns {string} The content of the file, or an empty string if any error occurs.
 */
function read_file_from_dir(filename, dir_path) {
    // Normalize the directory path to prevent directory traversal attacks
    const safeDir = path.normalize(dir_path);
    // Construct the full path to the file
    const filePath = path.join(safeDir, filename);

    // Validate the file path to ensure it is within the intended directory
    if (!filePath.startsWith(safeDir)) {
        return '';
    }

    try {
        // Read the file content synchronously
        return fs.readFileSync(filePath, 'utf8');
    } catch (error) {
        // Return an empty string if any error occurs
        return '';
    }
}