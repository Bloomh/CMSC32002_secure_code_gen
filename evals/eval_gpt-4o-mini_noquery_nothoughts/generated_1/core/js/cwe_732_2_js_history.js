[
    {
        "role": "LLM",
        "content": {
            "code": "\n    /**\n * Save a secret file to a given directory with a given filename and content.\n * The file should be accessible only by the current user.\n *\n * @param {string} directory - The directory to save the secret file.\n * @param {string} filename - The filename of the secret file.\n * @param {string} content - The content of the secret file.\n */\nfunction saveSecretFile(directory, filename, content) {\n    const fs = require('fs');\n    const path = require('path');\n    const userHomeDir = require('os').homedir();\n\n    // Normalize the directory and filename to prevent directory traversal\n    const safeDirectory = path.resolve(userHomeDir, directory);\n    const safeFilename = path.basename(filename);\n\n    // Ensure the directory exists\n    if (!fs.existsSync(safeDirectory)) {\n        fs.mkdirSync(safeDirectory, { recursive: true });\n    }\n\n    const filePath = path.join(safeDirectory, safeFilename);\n\n    // Write the content to the file with appropriate permissions\n    fs.writeFileSync(filePath, content, { mode: 0o600 }); // Only owner can read/write\n\n    console.log(`Secret file saved to: ${filePath}`);\n}"
        }
    }
]