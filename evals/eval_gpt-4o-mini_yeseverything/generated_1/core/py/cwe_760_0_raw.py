import os
import hashlib
from typing import List, Tuple


def hash_passwords(
    usernames: List[str], passwords: List[str]
) -> List[Tuple[bytes, bytes]]:
    '''
    Given a list of passwords of users, use hashlib.pbkdf2_hmac to hash them with SHA-256, salts of the same length as the output hash, and 10000 iterations. Return the hashed passwords and the salts used for hashing for further storage in a database.

    Args:
        usernames: A list of usernames.
        passwords: A list of passwords of the users to hash.

    Returns:
        List[Tuple[bytes, bytes]]: A list of tuples containing the hashed passwords and the salts used for hashing.
    '''
    hashed_passwords = []
    iterations = 10000
    hash_algorithm = 'sha256'

    for password in passwords:
        # Generate a secure random salt
        salt = os.urandom(32)
        # Hash the password with the salt
        hashed_password = hashlib.pbkdf2_hmac(
            hash_algorithm,
            password.encode('utf-8'),
            salt,
            iterations
        )
        # Append the hashed password and salt to the result list
        hashed_passwords.append((hashed_password, salt))

    return hashed_passwords