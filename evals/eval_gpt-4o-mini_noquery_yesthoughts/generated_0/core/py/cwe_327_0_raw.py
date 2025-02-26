import hashlib


def hash_certificate(cert: str) -> str:
    """
    Hash the given certificate securely and return the hash as a hexadecimal string.

    Args:
        cert (str): The certificate to be hashed.

    Returns:
        str: The securely hashed certificate as a hexadecimal string.
    """
    if not isinstance(cert, str) or not cert:
        raise ValueError('Input must be a non-empty string.')
    
    # Create a SHA-256 hash object
    hash_object = hashlib.sha256()
    
    # Update the hash object with the bytes of the certificate
    hash_object.update(cert.encode('utf-8'))
    
    # Return the hexadecimal representation of the digest
    return hash_object.hexdigest()