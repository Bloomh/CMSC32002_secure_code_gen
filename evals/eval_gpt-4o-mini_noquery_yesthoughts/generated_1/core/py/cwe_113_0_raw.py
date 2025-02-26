from typing import Dict
import re
import logging


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
    valid_types = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }

    # Validate info_type
    header_key = valid_types.get(info_type)
    if header_key:
        # Sanitize the info_content using regex to allow only safe characters
        sanitized_content = re.sub(r'[^a-zA-Z0-9,;\-\s]', '', info_content.strip())
        if sanitized_content:
            header[header_key] = sanitized_content
            return header
        else:
            logging.warning('Sanitized content is empty after processing: %s', info_content)
    else:
        logging.warning('Invalid info_type provided: %s', info_type)
    return header