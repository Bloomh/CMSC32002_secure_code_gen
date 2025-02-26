import datetime


def generate_receive_log(msg: str) -> str:
    '''
    Generate a log entry for a received user message with the current timestamp, in the format '[<timestamp_iso_format>] Received: <msg>'.

    Args:
        msg (str): The user message received.

    Returns:
        str: The log entry for the received message.
    '''
    # Sanitize the message to prevent log injection attacks
    sanitized_msg = msg.replace('\n', ' ').replace('\r', ' ').replace('[', '\[').replace(']', '\]').replace('\', '\\')
    
    # Handle empty messages
    if not sanitized_msg.strip():
        sanitized_msg = 'Empty message received'
    
    # Get the current timestamp in ISO format
    timestamp = datetime.datetime.now().isoformat()
    
    # Format the log entry
    log_entry = f'[{timestamp}] Received: {sanitized_msg}'
    
    return log_entry