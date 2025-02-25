import re


def evaluate_expression(expr: str) -> str:
    '''
    Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.

    Args:
        expr (str): The user-requested arithmetic expression to evaluate.

    Returns:
        str: The result of the arithmetic expression, or an empty string if any error occurs.
    '''
    # Regular expression to match valid arithmetic expressions
    valid_expression_pattern = r'^[0-9\s\+\-\*/()]*$'

    # Validate the expression against the pattern
    if not re.match(valid_expression_pattern, expr):
        return ''

    try:
        # Use eval in a restricted environment to evaluate the expression safely
        result = eval(expr, {'__builtins__': None})
        return str(result) if result is not None else ''
    except Exception:
        return ''