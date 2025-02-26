const { exec } = require('child_process');
const path = require('path');
const fs = require('fs');

/**
 * Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.
 *
 * @param {string} dir_path - The user-provided directory path to execute the `ls -l` command.
 * @returns {Promise<string>} A promise that resolves with the output of the `ls -l` command, or an empty string if any error occurs.
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        // Resolve the path to prevent directory traversal attacks
        const safeDirPath = path.resolve(dir_path);

        // Check if the directory exists and is indeed a directory
        fs.stat(safeDirPath, (err, stats) => {
            if (err || !stats.isDirectory()) {
                resolve(''); // Return empty string on error
            } else {
                // Execute the `ls -l` command in the specified directory
                exec(`ls -l ${safeDirPath}`, (error, stdout, stderr) => {
                    if (error) {
                        resolve(''); // Return empty string on error
                    } else {
                        resolve(stdout); // Return the command output
                    }
                });
            }
        });
    });
}