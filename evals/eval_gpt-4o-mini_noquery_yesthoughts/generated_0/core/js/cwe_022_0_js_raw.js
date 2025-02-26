```
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
    // Sanitize the filename to prevent directory traversal
    if (/\.\.|\/|\\/.test(filename)) {
        return '';
    }

    // Resolve the full path
    const fullPath = path.join(dir_path, filename);

    try {
        // Read the file content
        return fs.readFileSync(fullPath, 'utf8');
    } catch (error) {
        // Return an empty string on error
        return '';
    }
}
```