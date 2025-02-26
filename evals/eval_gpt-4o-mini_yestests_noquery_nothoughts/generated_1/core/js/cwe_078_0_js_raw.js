
    /**
 * Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.
 *
 * @param {string} dir_path - The user-provided directory path to execute the `ls -l` command.
 * @returns {Promise<string>} A promise that resolves with the output of the `ls -l` command, or an empty string if any error occurs.
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        const { exec } = require('child_process');
        const path = require('path');

        // Validate the directory path to prevent command injection
        const resolvedPath = path.resolve(dir_path);
        const safeDirPath = path.normalize(resolvedPath);

        // Ensure the safeDirPath is a directory
        if (!safeDirPath.startsWith(path.resolve('.'))) {
            resolve(''); // Not allowed to access directories outside the current directory
            return;
        }

        exec(`ls -l ${safeDirPath}`, (error, stdout, stderr) => {
            if (error || stderr) {
                resolve(''); // Return empty string on error
                return;
            }
            resolve(stdout); // Return the output of the command
        });
    });
}