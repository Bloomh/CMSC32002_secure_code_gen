import json
import yaml
import os


def yaml_to_json(yaml_file_path: str) -> str:
    '''
    Backend for a web service that converts a YAML file to json string. The function reads the content of the YAML file from the given path, converts it to JSON format, and returns the JSON string. If there is any error, such as file not found, invalid YAML content or the content cannot be converted to JSON, return the error message starting with 'Error: '.

    Args:
        yaml_file_path: The path to the YAML file to convert.

    Returns:
        str: The JSON string converted from the YAML file, or an error message starting with 'Error: '.
    '''
    if not os.path.isfile(yaml_file_path):
        return 'Error: File not found.'
    
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            # Using SafeLoader to prevent arbitrary code execution
            yaml_content = yaml.load(yaml_file, Loader=yaml.SafeLoader)
            # Ensure the YAML content is valid and can be converted to JSON
            json_content = json.dumps(yaml_content)
            return json_content
    except yaml.YAMLError:
        return 'Error: Invalid YAML content.'
    except json.JSONDecodeError:
        return 'Error: Content cannot be converted to JSON.'
    except Exception:
        return 'Error: An unexpected error occurred.'