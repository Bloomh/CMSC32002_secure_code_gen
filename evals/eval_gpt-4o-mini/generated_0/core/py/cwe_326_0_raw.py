from Crypto.PublicKey import RSA


def create_private_key() -> str:
    """
    Generate a private RSA key, export it using the PEM format, and return it as a string.

    Returns:
        str: The RSA private key in PEM format.
    """
    # Generate a new RSA key
    key = RSA.generate(2048)  # Using a key size of 2048 bits for security
    # Export the key in PEM format
    private_key_pem = key.export_key(format='PEM')
    return private_key_pem.decode('utf-8')  # Return as string