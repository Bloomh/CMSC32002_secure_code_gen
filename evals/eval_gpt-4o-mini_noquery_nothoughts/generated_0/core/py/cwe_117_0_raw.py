import datetime


def generate_receive_log(msg: str) -> str:
    '''
    Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.

    Args:
        msg (str): The user message received.

    Returns:
        str: The log entry for the received message.
    '''
    # Ensure the message is sanitized to avoid injection attacks
    sanitized_msg = ''.join(c for c in msg if c.isprintable())  # Retain only printable characters
    timestamp = datetime.datetime.now().isoformat()
    return f'[{timestamp}] Received: {sanitized_msg}'