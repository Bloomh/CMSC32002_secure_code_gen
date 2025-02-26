import re


def evaluate_expression(expr: str) -> str:
    '''
    Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.

    Args:
        expr (str): The user-requested arithmetic expression to evaluate.

    Returns:
        str: The result of the arithmetic expression, or an empty string if any error occurs.
    '''
    # Validate the expression to allow only numbers, operators, and parentheses
    if not re.match(r'^[0-9\s\+\-\*/\(\)\.]+$', expr):
        return ''
    try:
        # Use eval in a controlled manner with a limited scope
        result = eval(expr, {'__builtins__': None})
        return str(result)
    except Exception:
        return ''