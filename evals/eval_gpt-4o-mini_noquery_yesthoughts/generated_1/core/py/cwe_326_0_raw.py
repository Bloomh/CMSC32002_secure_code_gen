from Crypto.PublicKey import RSA


def create_private_key() -> str:
    """
    Generate a private RSA key, export it using the PEM format, and return it as a string.

    Returns:
        str: The RSA private key in PEM format.
    """
    try:
        # Generate a new RSA key pair
        key = RSA.generate(2048)
        # Export the private key in PEM format
        private_key_pem = key.export_key(format='PEM')
        return private_key_pem.decode('utf-8')
    except Exception as e:
        raise RuntimeError('Failed to generate RSA private key: ' + str(e))