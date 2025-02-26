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
    # Define the key length for AES
    aes_key_length = 16  # AES-128
    # Use the first aes_key_length bytes of the provided key
    aes_key = key[:aes_key_length]
    # Create a new AES cipher in CBC mode with a random IV
    cipher = AES.new(aes_key, AES.MODE_CBC)
    iv = cipher.iv  # Get the IV used for encryption
    # Pad the data to make it a multiple of the block size
    padded_data = pad(data, AES.block_size)
    # Encrypt the padded data
    encrypted_data = cipher.encrypt(padded_data)
    return encrypted_data, iv, aes_key