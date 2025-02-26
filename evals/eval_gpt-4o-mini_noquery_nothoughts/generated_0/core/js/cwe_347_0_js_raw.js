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
        // Verify and decode the token using the provided key
        const decoded = jwt.verify(token, key);
        // Return only the payload of the decoded token
        return decoded && typeof decoded === 'object' ? decoded : {};
    } catch (error) {
        // Log the error for auditing purposes (avoid logging sensitive information)
        console.error('JWT decoding failed:', error.message);
        // If decoding fails, return an empty object
        return {};
    }
}