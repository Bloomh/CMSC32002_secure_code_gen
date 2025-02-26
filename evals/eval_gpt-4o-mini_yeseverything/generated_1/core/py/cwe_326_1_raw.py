from Crypto.PublicKey import DSA


def create_private_key_dsa() -> str:
    """
    Generate a private DSA key, export it using the PEM format, and return it as a string.

    Returns:
        str: The DSA private key in PEM format.
    """
    try:
        # Generate a DSA key with a safe key size (2048 bits is a good choice)
        key = DSA.generate(2048)
        # Export the private key in PEM format
        pem_key = key.export_key(format='PEM')
        return pem_key.decode('utf-8')
    except Exception as e:
        raise RuntimeError("Key generation failed: " + str(e))