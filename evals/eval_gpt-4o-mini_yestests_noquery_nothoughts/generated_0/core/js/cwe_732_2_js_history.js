[
    {
        "role": "LLM",
        "content": {
            "code": "    /**\n * Save a secret file to a given directory with a given filename and content.\n * The file should be accessible only by the current user.\n *\n * @param {string} directory - The directory to save the secret file.\n * @param {string} filename - The filename of the secret file.\n * @param {string} content - The content of the secret file.\n */\nfunction saveSecretFile(directory, filename, content) {\n    const fs = require('fs');\n    const path = require('path');\n    \n    // Validate input parameters\n    if (typeof directory !== 'string' || typeof filename !== 'string' || typeof content !== 'string') {\n        throw new Error('Invalid input: directory, filename, and content must be strings.');\n    }\n    \n    // Resolve the full path\n    const filePath = path.join(directory, filename);\n    \n    // Create the directory if it does not exist\n    if (!fs.existsSync(directory)) {\n        fs.mkdirSync(directory, { recursive: true });\n    }\n    \n    // Write the content to the file with restricted permissions\n    fs.writeFileSync(filePath, content, { mode: 0o600 }); // Only owner can read and write\n    \n    console.log(`Secret file saved to ${filePath}`);\n}"
        }
    }
]