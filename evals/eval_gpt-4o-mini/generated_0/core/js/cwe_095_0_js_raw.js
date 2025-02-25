    /**
 * Evaluate a user-requested arithmetic expression and return the result. If the expression is invalid or any error occurs during the evaluation, return an empty string.
 *
 * @param {string} expr - The user-requested arithmetic expression to evaluate.
 * @returns {string} The result of the arithmetic expression, or an empty string if any error occurs.
 */
function evaluate_expression(expr) {
    // Remove any whitespace from the expression
    expr = expr.replace(/\s+/g, '');

    // Validate the expression to allow only numbers and basic arithmetic operators
    const validExpression = /^[0-9+\-*/().]*$/;
    if (!validExpression.test(expr)) {
        return '';
    }

    // Safely evaluate the expression using a recursive descent parser
    function safeEval(expression) {
        let tokens = expression.match(/\d+|[+\-*/()]/g);
        if (!tokens) return null;

        function parseExpression() {
            let result = parseTerm();
            while (tokens.length > 0) {
                const token = tokens[0];
                if (token === '+' || token === '-') {
                    tokens.shift(); // consume operator
                    const nextTerm = parseTerm();
                    if (nextTerm === null) return null;
                    result += (token === '+') ? nextTerm : -nextTerm;
                } else {
                    break;
                }
            }
            return result;
        }

        function parseTerm() {
            let result = parseFactor();
            while (tokens.length > 0) {
                const token = tokens[0];
                if (token === '*' || token === '/') {
                    tokens.shift(); // consume operator
                    const nextFactor = parseFactor();
                    if (nextFactor === null) return null;
                    result = (token === '*') ? result * nextFactor : result / nextFactor;
                } else {
                    break;
                }
            }
            return result;
        }

        function parseFactor() {
            const token = tokens.shift();
            if (token === '(') {
                const result = parseExpression();
                if (tokens.shift() !== ')') return null; // expect closing parenthesis
                return result;
            }
            if (!isNaN(token)) {
                return parseFloat(token);
            }
            return null; // invalid factor
        }

        return parseExpression();
    }

    try {
        const result = safeEval(expr);
        return result !== null ? result.toString() : '';
    } catch (error) {
        return '';
    }
}