import datetime


def generate_receive_log(msg: str) -> str:
    '''
    Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.

    Args:
        msg (str): The user message received.

    Returns:
        str: The log entry for the received message.
    '''
    if not msg:
        raise ValueError('Message cannot be empty.')
    # Sanitize input to prevent log injection
    sanitized_msg = ' '.join(msg.split())  # This removes newlines and excessive whitespace
    timestamp = datetime.datetime.now().isoformat()
    log_entry = f'[{timestamp}] Received: {sanitized_msg}'
    return log_entry