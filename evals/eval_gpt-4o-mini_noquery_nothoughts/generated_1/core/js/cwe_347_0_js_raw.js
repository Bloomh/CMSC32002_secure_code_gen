const jwt = require('jsonwebtoken');

/**
 * Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty object. Note that you should only return the payload of the decoded thing.
 *
 * @param {string} token - The JWT token to decode.
 * @param {string} key - The key used in encoding.
 * @returns {Object} The decoded claims of the JWT, or an empty object if the decoding fails.
 */
function decodeJsonWebToken(token, key) {
    // Validate input types and values
    if (typeof token !== 'string' || typeof key !== 'string' || !token.trim() || !key.trim()) {
        return {};
    }
    try {
        // Verify the token and decode its payload
        const decoded = jwt.verify(token, key);
        // Ensure that the decoded result is an object and return it
        return typeof decoded === 'object' ? decoded : {};
    } catch (error) {
        // Log the error for debugging purposes
        console.error('JWT decoding error:', error);
        // Return an empty object if decoding fails
        return {};
    }
}