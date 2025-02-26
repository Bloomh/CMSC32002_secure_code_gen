import re


def evaluate_expression(expr: str) -> str:
    '''
    Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.

    Args:
        expr (str): The user-requested arithmetic expression to evaluate.

    Returns:
        str: The result of the arithmetic expression, or an empty string if any error occurs.
    '''
    # Validate the expression to allow only numbers and basic arithmetic operators
    if not re.match(r'^[\d\s+\-*/().]*$', expr):
        return ''

    try:
        # Safe evaluation using eval but with limited scope
        result = eval(expr, {'__builtins__': None})
        # Ensure the result is a number
        if isinstance(result, (int, float)):
            return str(result)
    except (ValueError, SyntaxError, TypeError):
        # Handle any errors during evaluation
        pass
    return ''