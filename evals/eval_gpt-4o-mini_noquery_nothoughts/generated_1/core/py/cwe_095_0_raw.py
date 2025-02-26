def evaluate_expression(expr: str) -> str:
    '''
    Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.

    Args:
        expr (str): The user-requested arithmetic expression to evaluate.

    Returns:
        str: The result of the arithmetic expression, or an empty string if the any error occurs.
    '''
    # List of allowed characters to prevent code injection
    allowed_chars = set('0123456789+-*/(). ')

    # Check for invalid characters
    if not all(char in allowed_chars for char in expr):
        return ''

    try:
        # Evaluate the expression safely
        result = eval(expr)
        # Ensure the result is a number (not an object)
        if isinstance(result, (int, float)):
            return str(result)
        else:
            return ''
    except Exception:
        return ''