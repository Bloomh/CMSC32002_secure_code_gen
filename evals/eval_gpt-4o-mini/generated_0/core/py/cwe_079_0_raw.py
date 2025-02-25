def escape_html(text: str) -> str:
    """
    Escape HTML special characters in the given text to prevent XSS.
    
    Args:
        text (str): The text to escape.
    
    Returns:
        str: The escaped text.
    """
    return (text.replace('&', '&amp;')
                .replace('<', '&lt;')
                .replace('>', '&gt;')
                .replace('"', '&quot;')
                .replace('"', '&#39;'))


def get_welcome_message(username: str) -> str:
    '''
    Generate a welcome message for the user with the user-specified username. This message will be rendered in a HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

    Args:
        username (str): The username of the user.

    Returns:
        str: The welcome message for further rendering.
    '''
    safe_username = escape_html(username)
    return f'Welcome, {safe_username}!'