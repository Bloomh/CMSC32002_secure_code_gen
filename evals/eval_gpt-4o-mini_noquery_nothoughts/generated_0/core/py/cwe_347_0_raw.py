import jwt


def decode_json_web_token(token: str, key: str) -> dict:
    """
    Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty dictionary.

    Args:
        token (str): The JWT token to decode.
        key (str): The key used in encoding.

    Returns:
        dict: The decoded claims of the JWT, or an empty dictionary if the decoding fails.
    """
    try:
        # Decode the token using the provided key and algorithm, allowing for verification
        decoded = jwt.decode(token, key, algorithms=['HS256'])
        return decoded
    except jwt.ExpiredSignatureError:
        # Handle expired token
        return {}
    except jwt.InvalidTokenError:
        # Handle invalid token
        return {}
    except Exception as e:
        # Log unexpected exceptions for security purposes
        print(f'An unexpected error occurred: {e}')  # In production, consider using a logging framework
        return {}