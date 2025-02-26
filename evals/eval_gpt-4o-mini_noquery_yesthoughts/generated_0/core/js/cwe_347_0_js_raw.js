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
        // Verify the token and decode it using the provided key
        const options = { algorithms: ['HS256'] }; // Specify the algorithm used for signing
        const decoded = jwt.verify(token, key, options);
        // Return only the payload from the decoded token
        return decoded;
    } catch (error) {
        // Log a generic error message without exposing sensitive information
        console.warn('Failed to decode token.');
        return {};
    }
}