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
        # Decode the token using the provided key and algorithm
        decoded = jwt.decode(token, key, algorithms=['HS256'])
        return decoded
    except jwt.ExpiredSignatureError:
        # Token has expired
        return {}
    except jwt.InvalidTokenError:
        # Token is invalid
        return {}
    except Exception as e:
        # Catch any other exceptions and return an empty dictionary
        return {}