```
/**
 * Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.
 *
 * @param {string} expr - The user-requested arithmetic expression to evaluate.
 * @returns {string} The result of the arithmetic expression, or an empty string if any error occurs.
 */
function evaluate_expression(expr) {
    // Allow only numbers, operators (+, -, *, /), and parentheses
    const sanitizedExpr = expr.replace(/[^0-9+\-*/().]/g, '');
    try {
        // Evaluate the sanitized expression safely
        const result = Function(`'use strict'; return (${sanitizedExpr})`)();
        return result !== undefined ? result.toString() : '';
    } catch (e) {
        return '';
    }
}
```