def evaluate_expression(expr: str) -> str:
    '''
    Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.

    Args:
        expr (str): The user-requested arithmetic expression to evaluate.

    Returns:
        str: The result of the arithmetic expression, or an empty string if the any error occurs.
    '''
    try:
        # Using eval with a restricted scope to limit potential security issues
        allowed_names = {'__builtins__': None}
        result = eval(expr, allowed_names)
        # Ensure the result is a number
        if isinstance(result, (int, float)):
            return str(result)
    except (SyntaxError, NameError, TypeError):
        pass
    return ''