/**
 * Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.
 *
 * @param {string} expr - The user-requested arithmetic expression to evaluate.
 * @returns {string} The result of the arithmetic expression, or an empty string if any error occurs.
 */
function evaluate_expression(expr) {
    try {
        // Validate the expression to ensure it only contains safe characters
        const validExpression = /^[0-9+\-*/()\s]*$/;
        if (!validExpression.test(expr)) {
            return '';
        }

        // Use a safer method to evaluate the expression
        // Replace any potential unsafe characters or patterns
        const sanitizedExpr = expr.replace(/[^0-9+\-*/()\s]/g, '');

        // Use the Function constructor to evaluate the sanitized expression
        const result = new Function('return ' + sanitizedExpr)();
        return result.toString();
    } catch (error) {
        return '';
    }
}