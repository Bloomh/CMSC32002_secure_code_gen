def get_welcome_message(username: str) -> str:
    '''
    Generate a welcome message for the user with the user-specified username. This message will be rendered in a HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

    Args:
        username (str): The username of the user.

    Returns:
        str: The welcome message for further rendering.
    '''
    # Import html module to escape the username
    import html
    # Escape the username to prevent XSS attacks
    safe_username = html.escape(username)
    return f'Welcome, {safe_username}!'