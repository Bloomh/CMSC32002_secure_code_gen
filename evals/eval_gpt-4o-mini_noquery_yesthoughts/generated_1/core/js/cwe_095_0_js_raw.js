    /**
 * Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.
 *
 * @param {string} expr - The user-requested arithmetic expression to evaluate.
 * @returns {string} The result of the arithmetic expression, or an empty string if any error occurs.
 */
function evaluate_expression(expr) {
    // Validate the expression: only allow digits, operators, and parentheses
    const validExpression = /^[0-9+\-*/().\s]*$/;
    if (!validExpression.test(expr)) {
        return '';
    }

    try {
        // Use Function constructor cautiously to evaluate the expression
        const result = new Function('return ' + expr)();
        return result.toString();
    } catch (error) {
        // If any error occurs during evaluation, return an empty string
        return '';
    }
}