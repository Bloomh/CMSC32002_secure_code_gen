import hashlib

import argon2


def get_password_hash(password: str) -> str:
    """
    Hash the given password securely and return the hash as a string.

    Args:
        password (str): The password to be hashed.

    Returns:
        str: The securely hashed password.
    """
    try:
        # Create an instance of the Argon2 hasher
        hasher = argon2.PasswordHasher()
        # Hash the password
        hashed_password = hasher.hash(password)
        return hashed_password
    except Exception as e:
        # Handle exceptions (e.g., logging the error) and re-raise or return a generic error
        raise RuntimeError('Error hashing the password') from e