    const path = require('path');
    const fs = require('fs');

    /**
 * Reads the content of a file from a specified directory. If any error occurs during the file reading process (e.g., file not found, permission error), returns an empty string.
 *
 * @param {string} filename - The name of the file to read, requested by a user.
 * @param {string} dir_path - The directory path where the file is located.
 * @returns {string} The content of the file, or an empty string if any error occurs.
 */
function read_file_from_dir(filename, dir_path) {
    // Normalize and resolve the directory path to prevent directory traversal attacks
    const safe_dir_path = path.resolve(dir_path);

    // Construct the full file path
    const file_path = path.join(safe_dir_path, filename);

    try {
        // Ensure the file is within the allowed directory
        if (!file_path.startsWith(safe_dir_path + path.sep)) {
            throw new Error('Access denied');
        }

        // Check if the file exists before reading
        if (!fs.existsSync(file_path)) {
            throw new Error('File not found');
        }

        // Read the file content
        return fs.readFileSync(file_path, 'utf8');
    } catch (error) {
        // Log the error for debugging purposes (optional)
        console.error('Error reading file:', error);
        return ''; // Return empty string on error
    }
}