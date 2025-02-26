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
    # Define a mapping of info types to header keys
    info_mapping = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }

    # Validate the info_type
    if info_type not in info_mapping:
        return header  # Return original header if info_type is invalid

    # Validate the info_content to prevent security issues (like header injection)
    if not isinstance(info_content, str) or '\n' in info_content or '\r' in info_content:
        return header  # Return original header if content is invalid

    # Sanitize the content to prevent unintended characters
    sanitized_content = ''.join(c for c in info_content if c.isprintable()).strip()

    # Update the header with the sanitized content
    header[info_mapping[info_type]] = sanitized_content
    return header