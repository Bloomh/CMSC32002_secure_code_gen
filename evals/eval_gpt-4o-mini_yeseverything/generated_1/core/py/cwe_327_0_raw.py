import hashlib


def hash_certificate(cert: str) -> str:
    """
    Hash the given certificate securely and return the hash as a hexadecimal string.

    Args:
        cert (str): The certificate to be hashed.

    Returns:
        str: The securely hashed certificate as a hexadecimal string.
    """
    # Ensure the input is in bytes, as hashlib requires bytes-like objects
    cert_bytes = cert.encode('utf-8')
    # Use SHA-256 to hash the certificate
    hash_object = hashlib.sha256(cert_bytes)
    # Return the hexadecimal representation of the hash
    return hash_object.hexdigest()