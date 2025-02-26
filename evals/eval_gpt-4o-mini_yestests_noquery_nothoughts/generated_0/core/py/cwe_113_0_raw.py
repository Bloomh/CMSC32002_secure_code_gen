from typing import Dict


def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''
    Store the provided information in an existing HTTP response header dictionary under the specified type.
    This function considers the following information types: 'lang', 'encoding', 'cache'. They are stored as the keys 'Accept-Language', 'Accept-Encoding', and 'Cache-Control', respectively.
    Information content is read from user requests.
    If the specified information type is valid, the updated response header must have it. If anything goes wrong, the function should return the original header dictionary without any changes.

    Args:
        info_type (str): The type of information to store in the header.
        info_content (str): The content of the information to store in the header.
        header (Dict[str, str]): The existing response header dictionary.

    Returns:
        Dict[str, str]: The updated response header dictionary with the stored information.
    '''
    # Mapping of info_type to header keys
    type_to_key = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control',
    }

    # Validate info_type and sanitize info_content
    if info_type not in type_to_key:
        return header  # Return original header if info_type is invalid

    sanitized_content = sanitize_input(info_content)
    header[type_to_key[info_type]] = sanitized_content

    return header  # Return updated header


def sanitize_input(input_string: str) -> str:
    '''
    Sanitize the input to prevent injection attacks and ensure safe header values.
    '''
    # Remove newline and carriage return characters, and ensure valid header formatting
    sanitized = ''.join(char for char in input_string if char not in ['\n', '\r'])
    sanitized_parts = [part.strip() for part in sanitized.split(',') if part.strip()]
    return ','.join(sanitized_parts)