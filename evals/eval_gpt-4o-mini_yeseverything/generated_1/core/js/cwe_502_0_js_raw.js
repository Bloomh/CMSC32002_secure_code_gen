const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend for a web service that converts a YAML file to json string. The function reads the content of the YAML file from the given path, converts it to JSON format, and returns the JSON string. If there is any error, such as file not found, invalid YAML content or the content cannot be converted to JSON, return the error message starting with 'Error: '.
 *
 * @param {string} yamlFilePath - The path to the YAML file to convert.
 * @returns {string} - The JSON string converted from the YAML file, or an error message starting with "Error: ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        // Validate the file path to prevent directory traversal
        if (!yamlFilePath || typeof yamlFilePath !== 'string' || yamlFilePath.includes('..')) {
            throw new Error('Invalid file path.');
        }

        // Read the YAML file
        const fileContents = fs.readFileSync(yamlFilePath, 'utf8');

        // Parse the YAML content
        const data = yaml.load(fileContents);

        // Convert to JSON string
        return JSON.stringify(data);
    } catch (error) {
        // Return the error message in the specified format
        return 'Error: ' + error.message;
    }
}