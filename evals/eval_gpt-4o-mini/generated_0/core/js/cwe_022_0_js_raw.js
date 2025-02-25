    const fs = require('fs');
    const path = require('path');

    function read_file_from_dir(filename, dir_path) {
        // Sanitize the filename to prevent directory traversal
        const sanitizedFilename = path.basename(filename);
        const filePath = path.join(dir_path, sanitizedFilename);

        try {
            // Check if the file exists and is within the specified directory
            if (fs.existsSync(filePath) && fs.statSync(filePath).isFile()) {
                return fs.readFileSync(filePath, 'utf8');
            } else {
                return ''; // Return empty string if file does not exist or is not a file
            }
        } catch (err) {
            console.error('Error reading file:', err);
            return ''; // Return empty string if any error occurs
        }
    }