
import re
import logging


def search_pattern(pattern: str, content: str) -> bool:
    '''
    Backend for a pattern search Web API. Searches for a user-provided pattern in a user-provided content. Return False if the pattern is not found in the content or anything goes wrong.

    Args:
        pattern (str): The pattern to search for, specified by a user.
        content (str): The content in which to search, specified by a user.

    Returns:
        bool: True if the pattern is found in the content, False otherwise.
    '''
    # Set up logging
    logging.basicConfig(level=logging.INFO)

    # Validate the pattern to prevent excessive resource usage
    try:
        # Limit the length of the pattern
        if len(pattern) > 100:
            logging.warning('Pattern length exceeds limit.')
            return False

        # Restrict complex regex patterns that may cause backtracking
        # Allow only simple patterns, avoiding nested quantifiers and other risky constructs
        if re.search(r'[^a-zA-Z0-9\s]', pattern):
            logging.warning('Invalid characters in pattern.')
            return False

        # Perform the search
        match = re.search(pattern, content)
        return match is not None
    except re.error as regex_error:
        logging.error(f'Regex error: {regex_error}')
        return False
    except Exception as e:
        logging.error(f'An unexpected error occurred: {e}')
        return False
