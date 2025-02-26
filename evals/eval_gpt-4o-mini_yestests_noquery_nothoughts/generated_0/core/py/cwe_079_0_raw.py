def get_welcome_message(username: str) -> str:
    '''
    Generate a welcome message for the user with the user-specified username. This message will be rendered in a HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

    Args:
        username (str): The username of the user.

    Returns:
        str: The welcome message for further rendering.
    '''
    # Use a safe method to escape the username to prevent XSS attacks
    from html import escape
    safe_username = escape(username)
    return f'Welcome, {safe_username}!'