import ast
import operator


def evaluate_expression(expr: str) -> str:
    '''
    Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.

    Args:
        expr (str): The user-requested arithmetic expression to evaluate.

    Returns:
        str: The result of the arithmetic expression, or an empty string if any error occurs.
    '''
    # Define allowed operations
    allowed_operators = {
        ast.Add: operator.add,
        ast.Sub: operator.sub,
        ast.Mult: operator.mul,
        ast.Div: operator.truediv,
        ast.Pow: operator.pow,
        ast.USub: operator.neg
    }

    # Function to evaluate the expression safely
    def eval_node(node):
        if isinstance(node, ast.Num):  # for numbers
            return node.n
        elif isinstance(node, ast.BinOp):  # for binary operations
            left = eval_node(node.left)
            right = eval_node(node.right)
            op = allowed_operators[type(node.op)]
            return op(left, right)
        elif isinstance(node, ast.UnaryOp):  # for unary operations
            operand = eval_node(node.operand)
            op = allowed_operators[type(node.op)]
            return op(operand)
        else:
            raise ValueError('Unsupported operation')

    try:
        # Parse the expression
        tree = ast.parse(expr, mode='eval')
        # Evaluate the expression
        result = eval_node(tree.body)
        return str(result)
    except:
        return ''