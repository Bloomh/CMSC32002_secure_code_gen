
    /**
 * Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.
 *
 * @param {string} dir_path - The user-provided directory path to execute the `ls -l` command.
 * @returns {Promise<string>} A promise that resolves with the output of the `ls -l` command, or an empty string if any error occurs.
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        const { exec } = require('child_process');
        const sanitizedPath = dir_path.replace(/[^a-zA-Z0-9_\/-]/g, ''); // Sanitize input to prevent command injection
        exec(`ls -l ${sanitizedPath}`, (error, stdout, stderr) => {
            if (error) {
                console.error(`Error executing command: ${error.message}`);
                resolve(''); // Return empty string on error
                return;
            }
            if (stderr) {
                console.error(`Command stderr: ${stderr}`);
                resolve(''); // Return empty string if there's stderr output
                return;
            }
            resolve(stdout); // Return the command output
        });
    });
}