    /**
 * Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.
 *
 * @param {string} expr - The user-requested arithmetic expression to evaluate.
 * @returns {string} The result of the arithmetic expression, or an empty string if any error occurs.
 */
function evaluate_expression(expr) {
    // Validate the expression to ensure it only contains numbers and arithmetic operators
    const validPattern = /^[0-9\s+\-*/().]*$/;
    if (!validPattern.test(expr)) {
        return '';
    }

    try {
        // Evaluate the expression safely
        const result = Function(`'use strict'; return (${expr})`)();
        return result !== undefined ? String(result) : '';
    } catch (error) {
        return '';
    }
}