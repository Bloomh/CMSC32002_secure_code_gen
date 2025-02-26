const jwt = require('jsonwebtoken');

/**
 * Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty object. Note that you should only return the payload of the decoded thing.
 *
 * @param {string} token - The JWT token to decode.
 * @param {string} key - The key used in encoding.
 * @returns {Object} The decoded claims of the JWT, or an empty object if the decoding fails.
 */
function decodeJsonWebToken(token, key) {
    try {
        // Verify the token using the provided key
        const decoded = jwt.verify(token, key);
        return decoded;
    } catch (error) {
        // Handle specific error cases without exposing sensitive information
        switch (error.name) {
            case 'JsonWebTokenError':
                console.error('JWT decoding failed: Invalid token.');
                break;
            case 'TokenExpiredError':
                console.error('JWT decoding failed: Token has expired.');
                break;
            default:
                console.error('JWT decoding failed: An unexpected error occurred.');
        }
        return {};
    }
}