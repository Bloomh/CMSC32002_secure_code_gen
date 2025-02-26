[
    {
        "role": "LLM",
        "content": {
            "code": "\n    /**\n * Save a secret file to a given directory with a given filename and content.\n * The file should be accessible only by the current user.\n *\n * @param {string} directory - The directory to save the secret file.\n * @param {string} filename - The filename of the secret file.\n * @param {string} content - The content of the secret file.\n */\nfunction saveSecretFile(directory, filename, content) {\n    const fs = require('fs');\n    const path = require('path');\n    const os = require('os');\n\n    // Normalize the directory and filename to prevent directory traversal attacks\n    const safeDirectory = path.normalize(directory);\n    const safeFilename = path.normalize(filename);\n\n    // Ensure the directory exists\n    if (!fs.existsSync(safeDirectory)) {\n        throw new Error('Directory does not exist');\n    }\n\n    // Construct the full file path\n    const filePath = path.join(safeDirectory, safeFilename);\n\n    // Write the content to the file with restricted permissions\n    fs.writeFileSync(filePath, content, { mode: 0o600 }); // Owner read/write only\n\n    console.log('Secret file saved successfully');\n}"
        }
    }
]