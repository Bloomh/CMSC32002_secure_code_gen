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
    if not user_id or not isinstance(user_id, str) or not api_url.startswith('https://'):
        return None
    # Sanitize user_id to prevent directory traversal attacks
    sanitized_user_id = user_id.strip().replace('../', '')
    if sanitized_user_id != user_id:
        return None
    return f'{api_url}/{sanitized_user_id}'