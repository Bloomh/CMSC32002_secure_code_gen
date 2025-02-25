import hashlib
import os
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
    if len(usernames) != len(passwords):
        raise ValueError("Usernames and passwords lists must have the same length.")

    hashed_passwords = []
    iterations = 10000
    hash_length = 32  # SHA-256 outputs 32 bytes

    for password in passwords:
        # Generate a random salt
        salt = os.urandom(hash_length)
        # Hash the password with the salt
        hashed_password = hashlib.pbkdf2_hmac(
            'sha256',
            password.encode('utf-8'),
            salt,
            iterations,
            dklen=hash_length
        )
        hashed_passwords.append((hashed_password, salt))

    return hashed_passwords