    return new Promise((resolve) => {
        const { exec } = require('child_process');
        // Validate the directory path to prevent command injection
        const safeDirPath = dir_path.replace(/[^a-zA-Z0-9_\/.-]/g, '');
        exec(`ls -l ${safeDirPath}`, (error, stdout, stderr) => {
            if (error) {
                // If any error occurs, return an empty string
                resolve('');
                return;
            }
            // Resolve with the stdout output
            resolve(stdout);
        });
    });
}