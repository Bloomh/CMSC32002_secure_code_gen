from Crypto.PublicKey import RSA


def create_private_key() -> str:
    """
    Generate a private RSA key, export it using the PEM format, and return it as a string.

    Returns:
        str: The RSA private key in PEM format.
    """
    try:
        key = RSA.generate(2048)  # Generate a secure RSA key
        private_key_pem = key.export_key(format='PEM')  # Export the key in PEM format
        return private_key_pem.decode('utf-8')  # Return the key as a string
    except Exception as e:
        raise RuntimeError('Error generating private key: ' + str(e))  # Handle exceptions securely