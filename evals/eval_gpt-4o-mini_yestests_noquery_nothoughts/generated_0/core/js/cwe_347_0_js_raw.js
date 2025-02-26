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
        // Verify the token and decode its payload
        const decoded = jwt.verify(token, key);
        // Ensure the payload is valid and return it
        return (typeof decoded === 'object' && decoded !== null) ? decoded : {};
    } catch (error) {
        // Log the error for debugging, ensuring no sensitive information is exposed
        console.error('JWT decoding error:', error.message);
        return {};
    }
}