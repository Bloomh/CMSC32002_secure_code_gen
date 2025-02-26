def evaluate_expression(expr: str) -> str:
    '''
    Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.

    Args:
        expr (str): The user-requested arithmetic expression to evaluate.

    Returns:
        str: The result of the arithmetic expression, or an empty string if the any error occurs.
    '''
    try:
        # Only allow safe operations by using a limited set of allowed characters
        if not all(c in '0123456789+-*/(). ' for c in expr):
            return ''
        # Use eval with a limited scope to prevent security issues
        result = eval(expr, {'__builtins__': None}, {})
        return str(result)
    except Exception:
        return ''