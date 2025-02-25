from typing import Tuple

from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad


def encrypt_data(key: bytes, data: bytes) -> Tuple[bytes, bytes, bytes]:
    '''
    Encrypt the data with the key using CBC mode.
    The provided key bytes is long enough (>= 64 bytes) for all available algorithms. Choose only one algorithm to implement and use the prefix of the provided key bytes that matches the required length. Do NOT choose the algorithm based on the length of the key.
    Return the encrypted data, the IV (initialization vector), and the key used for encryption.

    Args:
        key (bytes): The bytes to generate the encryption key.
        data (bytes): The data to encrypt.

    Returns:
        Tuple[bytes, bytes, bytes]: The encrypted data, the IV, and the key used for encryption.
    '''
    # Choose AES as the encryption algorithm
    # Ensure the key is 16, 24, or 32 bytes long
    AES_KEY_LENGTHS = [16, 24, 32]
    aes_key = key[:32]  # Use the first 32 bytes for AES, which is the max length

    # Validate key length
    if len(aes_key) not in AES_KEY_LENGTHS:
        raise ValueError("Key length must be 16, 24, or 32 bytes for AES.")

    # Generate a random IV
    iv = get_random_bytes(AES.block_size)

    # Create the AES cipher in CBC mode
    cipher = AES.new(aes_key, AES.MODE_CBC, iv)

    # Pad the data and encrypt it
    padded_data = pad(data, AES.block_size)
    encrypted_data = cipher.encrypt(padded_data)

    return encrypted_data, iv, aes_key