from Crypto.PublicKey import DSA


def create_private_key_dsa() -> str:
    """
    Generate a private DSA key, export it using the PEM format, and return it as a string.

    Returns:
        str: The DSA private key in PEM format.
    """
    try:
        # Generate a new DSA key with a secure size (2048 bits)
        dsa_key = DSA.generate(2048)
        # Export the private key to PEM format
        private_key_pem = dsa_key.export_key(format='PEM')
        return private_key_pem.decode('utf-8')
    except ValueError:
        raise RuntimeError("Invalid parameters for DSA key generation")
    except Exception as e:
        raise RuntimeError("An error occurred while generating the DSA private key") from e