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
        // Ensure the file exists and is readable
        if (!fs.existsSync(yamlFilePath)) {
            return 'Error: File not found';
        }

        // Read the YAML file
        const fileContent = fs.readFileSync(yamlFilePath, 'utf8');

        // Parse the YAML content
        const data = yaml.load(fileContent);

        // Convert to JSON string without pretty print to match the expected output
        return JSON.stringify(data);
    } catch (error) {
        // Return error message for various failure cases
        return `Error: ${error.message}`;
    }
}