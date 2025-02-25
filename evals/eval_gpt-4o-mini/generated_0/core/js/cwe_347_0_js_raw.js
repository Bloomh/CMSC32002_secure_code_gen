const jwt = require('jsonwebtoken');

/**
 * Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty object. Note that you should only return the payload of the decoded thing.
 *
 * @param {string} token - The JWT token to decode.
 * @param {string} key - The key used in encoding.
 * @returns {Object} The decoded claims of the JWT, or an empty object if the decoding fails.
 */
function decodeJsonWebToken(token, key) {
    if (typeof token !== 'string' || typeof key !== 'string' || !token.trim() || !key.trim()) {
        console.warn('Invalid token or key provided.');
        return {};
    }
    // Check the structure of the token (should have 2 dots)
    const tokenParts = token.split('.');
    if (tokenParts.length !== 3) {
        console.warn('Malformed JWT token.');
        return {};
    }
    // Check key strength (example: must be at least 32 characters)
    if (key.length < 32) {
        console.warn('Key provided is too short.');
        return {};
    }
    try {
        const decoded = jwt.verify(token, key);
        return decoded;
    } catch (error) {
        console.error('JWT decoding error:', error.message);
        return {};
    }
}