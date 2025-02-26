import re


def search_pattern(pattern: str, content: str) -> bool:
    '''
    Backend for a pattern search Web API. Searches for a user-provided pattern in a user-provided content. Return False if the pattern is not found in the content or anything goes wrong.

    Args:
        pattern (str): The pattern to search for, specified by a user.
        content (str): The content in which to search, specified by a user.

    Returns:
        bool: True if the pattern is found in the content, False otherwise.
    '''
    # Limit the length of the pattern and content to prevent excessive resource usage
    MAX_PATTERN_LENGTH = 100
    MAX_CONTENT_LENGTH = 10000

    if len(pattern) > MAX_PATTERN_LENGTH:
        raise ValueError(f"Pattern exceeds maximum length of {MAX_PATTERN_LENGTH} characters.")
    if len(content) > MAX_CONTENT_LENGTH:
        raise ValueError(f"Content exceeds maximum length of {MAX_CONTENT_LENGTH} characters.")

    try:
        # Compile the regex pattern to check for validity
        regex = re.compile(pattern)
        # Search for the pattern in the content
        return bool(regex.search(content))
    except re.error:
        # Regex pattern is invalid, return False
        return False
    except Exception as e:
        # Catch any other exceptions and return False
        print(f'An error occurred: {e}')
        return False