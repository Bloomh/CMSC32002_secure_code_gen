
const fs = require('fs');
const path = require('path');
const yaml = require('js-yaml');

/**
 * Backend for a web service that converts a YAML file to json string. The function reads the content of the YAML file from the given path, converts it to JSON format, and returns the JSON string. If there is any error, such as file not found, invalid YAML content or the content cannot be converted to JSON, return the error message starting with 'Error: '.
 *
 * @param {string} yamlFilePath - The path to the YAML file to convert.
 * @returns {Promise<string>} - The JSON string converted from the YAML file, or an error message starting with "Error: ".
 */
async function yaml_to_json(yamlFilePath) {
    try {
        // Validate the file path
        if (typeof yamlFilePath !== 'string' || !yamlFilePath.endsWith('.yaml')) {
            throw new Error('Invalid file path');
        }

        // Resolve the absolute path and check for directory traversal
        const resolvedPath = path.resolve(yamlFilePath);
        if (!resolvedPath.startsWith(path.resolve('.'))) {
            throw new Error('Access to this file is not allowed.');
        }

        // Check if the file exists
        await fs.promises.access(resolvedPath);

        // Read the YAML file asynchronously
        const fileContent = await fs.promises.readFile(resolvedPath, 'utf8');

        // Parse the YAML content
        let yamlContent;
        try {
            yamlContent = yaml.load(fileContent);
        } catch (parseError) {
            throw new Error('Invalid YAML content');
        }

        // Convert to JSON
        const jsonString = JSON.stringify(yamlContent, null, 2);
        return jsonString;
    } catch (error) {
        // Handle errors and return formatted error message
        return `Error: ${error.message}`;
    }
}