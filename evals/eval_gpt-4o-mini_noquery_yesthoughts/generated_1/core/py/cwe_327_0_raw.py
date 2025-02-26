import hashlib


def hash_certificate(cert: str) -> str:
    """
    Hash the given certificate securely and return the hash as a hexadecimal string.

    Args:
        cert (str): The certificate to be hashed.

    Returns:
        str: The securely hashed certificate as a hexadecimal string.
    """
    try:
        # Ensure the certificate is in bytes
        cert_bytes = cert.encode('utf-8')
        # Create a SHA-256 hash object
        sha256_hash = hashlib.sha256()
        # Update the hash object with the bytes-like object
        sha256_hash.update(cert_bytes)
        # Return the hexadecimal representation of the digest
        return sha256_hash.hexdigest()
    except Exception as e:
        raise ValueError(f'Error hashing certificate: {e}')