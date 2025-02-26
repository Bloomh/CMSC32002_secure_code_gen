import json
import yaml
from yaml import SafeLoader


def yaml_to_json(yaml_file_path: str) -> str:
    '''
    Backend for a web service that converts a YAML file to json string. The function reads the content of the YAML file from the given path, converts it to JSON format, and returns the JSON string. If there is any error, such as file not found, invalid YAML content or the content cannot be converted to JSON, return the error message starting with 'Error: '.

    Args:
        yaml_file_path: The path to the YAML file to convert.

    Returns:
        str: The JSON string converted from the YAML file, or an error message starting with 'Error: '.
    '''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            # Load the YAML content securely using SafeLoader
            yaml_content = yaml.load(yaml_file, Loader=SafeLoader)
            # Convert YAML to JSON
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Error: File not found'
    except yaml.YAMLError:
        return 'Error: Invalid YAML content'
    except TypeError:
        return 'Error: Content cannot be converted to JSON'
    except Exception as e:
        return f'Error: {str(e)}'