from Crypto.PublicKey import DSA


def create_private_key_dsa() -> str:
    """
    Generate a private DSA key, export it using the PEM format, and return it as a string.

    Returns:
        str: The DSA private key in PEM format.
    """
    try:
        # Generate a DSA key with a secure size (2048 bits is recommended)
        key = DSA.generate(2048)
        # Export the private key in PEM format
        private_key_pem = key.export_key(format='PEM')
        return private_key_pem.decode('utf-8')
    except Exception as e:
        raise RuntimeError(f'Failed to generate DSA private key: {e}')