[
    {
        "role": "LLM",
        "content": {
            "code": "\n/**\n * Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.\n *\n * @param {string} dir_path - The user-provided directory path to execute the `ls -l` command.\n * @returns {Promise<string>} A promise that resolves with the output of the `ls -l` command, or an empty string if any error occurs.\n */\nfunction get_ls_result(dir_path) {\n    return new Promise((resolve) => {\n        // Validate the directory path to prevent command injection\n        const sanitizedPath = dir_path.replace(/[^a-zA-Z0-9_./-]/g, '');\n        const { exec } = require('child_process');\n        exec(`ls -l ${sanitizedPath}`, (error, stdout, stderr) => {\n            if (error) {\n                console.error(`Error executing command: ${stderr}`);\n                resolve(''); // Return an empty string on error\n            } else {\n                resolve(stdout); // Return the command output\n            }\n        });\n    });\n}"
        }
    }
]