import hashlib


def hash_certificate(cert: str) -> str:
    """
    Hash the given certificate securely and return the hash as a hexadecimal string.

    Args:
        cert (str): The certificate to be hashed.

    Returns:
        str: The securely hashed certificate as a hexadecimal string.
    """
    # Use SHA-256 for hashing, which is a part of the SHA-2 family and is considered secure.
    hasher = hashlib.sha256()
    # Update the hasher with the certificate bytes, ensuring it is encoded properly.
    hasher.update(cert.encode('utf-8'))
    # Return the hexadecimal representation of the digest.
    return hasher.hexdigest()