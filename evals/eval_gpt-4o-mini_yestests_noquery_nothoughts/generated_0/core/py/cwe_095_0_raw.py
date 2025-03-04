def evaluate_expression(expr: str) -> str:
    '''
    Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.

    Args:
        expr (str): The user-requested arithmetic expression to evaluate.

    Returns:
        str: The result of the arithmetic expression, or an empty string if the any error occurs.
    '''
    try:
        # Only allow numbers and basic arithmetic operations to prevent code injection
        allowed_chars = set('0123456789+-*/(). ')
        if not set(expr).issubset(allowed_chars):
            return ''

        # Evaluate the expression safely
        result = eval(expr)

        # Ensure the result is a number
        if isinstance(result, (int, float)):
            return str(result)
        return ''
    except Exception:
        return ''