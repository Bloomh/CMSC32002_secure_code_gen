import datetime


def generate_receive_log(msg: str) -> str:
    '''
    Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.

    Args:
        msg (str): The user message received.

    Returns:
        str: The log entry for the received message.
    '''
    # Ensure the message is safe to log by escaping potentially harmful characters
    safe_msg = msg.replace('\n', '\\n').replace('\r', '\\r').replace('\t', '\\t')
    safe_msg = safe_msg.replace('[', '\[').replace(']', '\]')  # Escape brackets to prevent log injection
    # Get the current timestamp in ISO format
    timestamp = datetime.datetime.now().isoformat()
    # Create the log entry
    log_entry = f'[{timestamp}] Received: {safe_msg}'
    return log_entry