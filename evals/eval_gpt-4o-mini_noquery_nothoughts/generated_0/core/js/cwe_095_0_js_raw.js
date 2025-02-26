
    /**
 * Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.
 *
 * @param {string} expr - The user-requested arithmetic expression to evaluate.
 * @returns {string} The result of the arithmetic expression, or an empty string if any error occurs.
 */
function evaluate_expression(expr) {
    // Validate the input to allow only safe arithmetic operations
    const safeRegex = /^[0-9\s+\-*/().]*$/;
    if (!safeRegex.test(expr)) {
        return '';
    }

    try {
        // Use Function constructor to evaluate the expression safely
        const result = new Function('return ' + expr)();
        return result.toString();
    } catch (error) {
        // Return an empty string if an error occurs
        return '';
    }
}