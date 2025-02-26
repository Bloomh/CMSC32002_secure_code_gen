import operator
import re


def evaluate_expression(expr: str) -> str:
    '''
    Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.

    Args:
        expr (str): The user-requested arithmetic expression to evaluate.

    Returns:
        str: The result of the arithmetic expression, or an empty string if any error occurs.
    '''
    # Define allowed operators
    operators = {
        '+': operator.add,
        '-': operator.sub,
        '*': operator.mul,
        '/': operator.truediv,
        '**': operator.pow,
    }

    # Remove whitespace and validate the expression
    expr = expr.replace(' ', '')
    if not re.match(r'^[0-9+\-*/().**]+$', expr):
        return ''

    # Create a simple evaluation function
    def eval_simple_expr(expr):
        # Basic evaluation logic (you can expand this with more sophisticated parsing)
        try:
            # Evaluate the expression safely
            result = eval(expr, {'__builtins__': None}, operators)
            return str(result)
        except (SyntaxError, ZeroDivisionError):
            return ''

    # Evaluate the expression
    return eval_simple_expr(expr)