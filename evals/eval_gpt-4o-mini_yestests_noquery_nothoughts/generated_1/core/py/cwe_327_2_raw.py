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
    # Use AES with a key length of 16 bytes (128 bits)
    aes_key = key[:16]  # Use the first 16 bytes of the provided key
    cipher = AES.new(aes_key, AES.MODE_CBC)
    iv = cipher.iv  # Get the initialization vector
    padded_data = pad(data, AES.block_size)  # Pad data to be multiple of block size
    encrypted_data = cipher.encrypt(padded_data)  # Encrypt the padded data
    return encrypted_data, iv, aes_key