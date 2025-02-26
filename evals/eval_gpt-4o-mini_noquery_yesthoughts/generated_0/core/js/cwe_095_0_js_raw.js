```
/**
 * Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.
 *
 * @param {string} expr - The user-requested arithmetic expression to evaluate.
 * @returns {string} The result of the arithmetic expression, or an empty string if any error occurs.
 */
function evaluate_expression(expr) {
    try {
        // Importing a safe math library (mathjs) to evaluate the expression
        const math = require('mathjs');
        // Validate the expression to allow only safe characters
        const sanitizedExpr = expr.replace(/[^0-9+\-*/(). ]/g, '');
        // Check if the sanitized expression is empty or malformed
        if (!sanitizedExpr || sanitizedExpr.trim() === '') {
            return '';
        }
        // Evaluate the sanitized expression
        const result = math.evaluate(sanitizedExpr);
        return result.toString();
    } catch (error) {
        // Log the error for debugging purposes
        console.error('Error evaluating expression:', error);
        // Return an empty string if any error occurs during evaluation
        return '';
    }
}
```