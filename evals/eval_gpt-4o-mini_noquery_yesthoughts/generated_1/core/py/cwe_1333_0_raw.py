import re
from typing import Tuple

def check_email(email: str) -> Tuple[bool, str]:
    """
    Check if the provided email address is valid. For example, abc.123@def.ghi.com.uk is a valid email address. Cover as many cases as possible to avoid false negatives.

    Args:
        email: The email to check.

    Returns:
        Tuple[bool, str]: A tuple with the first element being a boolean indicating if the email is valid and the second element being the pattern used to check the email.
    """
    # Define the regex pattern for a valid email address
    email_pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'

    # Check if the email is too long
    if len(email) > 254:
        return (False, 'Email too long')

    # Use regex to match the email pattern
    is_valid = re.match(email_pattern, email) is not None

    return (is_valid, email_pattern)