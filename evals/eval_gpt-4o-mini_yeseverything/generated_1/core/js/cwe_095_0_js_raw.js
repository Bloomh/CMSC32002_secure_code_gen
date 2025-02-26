```
/**
 * Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.
 *
 * @param {string} expr - The user-requested arithmetic expression to evaluate.
 * @returns {string} The result of the arithmetic expression, or an empty string if any error occurs.
 */
function evaluate_expression(expr) {
    // Regular expression to validate the expression: allows digits, +, -, *, /, **, and whitespace.
    const validExpression = /^[0-9\s+\-*/()**]*$/;

    // Check if the expression is valid.
    if (!validExpression.test(expr)) {
        return '';
    }

    try {
        // Parse and evaluate the expression safely.
        const result = safeEvaluate(expr);
        return result !== undefined ? result.toString() : '';
    } catch (error) {
        return '';
    }
}

/**
 * Safely evaluates a simple arithmetic expression without using eval.
 * @param {string} expr - The expression to evaluate.
 * @returns {number} The result of the evaluated expression.
 */
function safeEvaluate(expr) {
    // Replace '**' with a temporary operator to handle exponentiation
    expr = expr.replace(/\*\*/g, ' ^ ');
    const tokens = expr.match(/\d+|[+\-*/()^]/g);
    const output = [];
    const operators = [];

    const precedence = {'+': 1, '-': 1, '*': 2, '/': 2, '^': 3};

    const applyOperator = (b, a, operator) => {
        switch (operator) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
            case '^': return Math.pow(a, b);
        }
    };

    for (const token of tokens) {
        if (!isNaN(token)) {
            output.push(parseFloat(token));
        } else if (token in precedence) {
            while (operators.length && precedence[operators[operators.length - 1]] >= precedence[token]) {
                const operator = operators.pop();
                const b = output.pop();
                const a = output.pop();
                output.push(applyOperator(b, a, operator));
            }
            operators.push(token);
        } else if (token === '(') {
            operators.push(token);
        } else if (token === ')') {
            while (operators.length && operators[operators.length - 1] !== '(') {
                const operator = operators.pop();
                const b = output.pop();
                const a = output.pop();
                output.push(applyOperator(b, a, operator));
            }
            operators.pop(); // Remove '('
        }
    }

    while (operators.length) {
        const operator = operators.pop();
        const b = output.pop();
        const a = output.pop();
        output.push(applyOperator(b, a, operator));
    }

    return output[0];
}
```