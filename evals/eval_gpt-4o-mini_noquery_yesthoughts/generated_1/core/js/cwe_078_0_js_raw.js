const { exec } = require('child_process');

/**
 * Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.
 *
 * @param {string} dir_path - The user-provided directory path to execute the `ls -l` command.
 * @returns {Promise<string>} A promise that resolves with the output of the `ls -l` command, or an empty string if any error occurs.
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        // Validate the directory path to prevent command injection
        if (typeof dir_path !== 'string' || !dir_path.match(/^([a-zA-Z0-9_./-]+)$/)) {
            resolve('');
            return;
        }

        // Execute the command safely
        exec(`ls -l ${dir_path}`, (error, stdout, stderr) => {
            if (error) {
                // If there's an error, return an empty string
                resolve('');
                return;
            }
            // Return the output of the command
            resolve(stdout);
        });
    });
}