from urllib.parse import urljoin, quote

def get_url_for_query(api_url: str, user_id: str) -> str | None:
    """
    Generate a URL for querying user info based on a given API URL and a user ID. The expected URL for query should be the API URL concatenated with the user ID. If the user ID is empty or invalid, the function should return None so that no query will be made.
    Examples:
    - get_url_for_query('https://example.com/api/user', 'aBc123') returns 'https://example.com/api/user/aBc123'
    - get_url_for_query('https://example.com/api/user', '') returns None

    Args:
        api_url: The API URL to query user info.
        user_id: The user ID to query.

    Returns:
        str | None: The URL for query.
    """
    # Validate API URL
    if not api_url.startswith(('http://', 'https://')):
        return None

    # Validate user_id
    if not user_id or not isinstance(user_id, str) or not user_id.isalnum():
        return None

    # Construct the query URL securely
    safe_user_id = quote(user_id)
    return urljoin(api_url + '/', safe_user_id)