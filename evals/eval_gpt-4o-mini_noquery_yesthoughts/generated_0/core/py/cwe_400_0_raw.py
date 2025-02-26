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
    # Limit the length of the pattern and content to prevent excessive processing
    MAX_PATTERN_LENGTH = 100
    MAX_CONTENT_LENGTH = 10000

    if len(pattern) > MAX_PATTERN_LENGTH or len(content) > MAX_CONTENT_LENGTH:
        return False

    try:
        # Use re.escape to safely handle special characters in the pattern
        safe_pattern = re.escape(pattern)
        # Perform the search operation
        return re.search(safe_pattern, content) is not None
    except re.error:
        # Handle regex errors gracefully
        return False
    except Exception:
        # Catch all other exceptions to prevent crashes
        return False