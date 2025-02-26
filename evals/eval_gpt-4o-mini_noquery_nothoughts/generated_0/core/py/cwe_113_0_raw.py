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
    # Validate the info_content to prevent header injection vulnerabilities
    if not isinstance(info_content, str) or '\r' in info_content or '\n' in info_content:
        return header

    # Define mapping for valid info types
    valid_info_types = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }

    # Check if the provided info_type is valid
    if info_type in valid_info_types:
        # Update the header with the sanitized content
        sanitized_content = info_content.strip()  # Additional sanitization
        header[valid_info_types[info_type]] = sanitized_content

    return header