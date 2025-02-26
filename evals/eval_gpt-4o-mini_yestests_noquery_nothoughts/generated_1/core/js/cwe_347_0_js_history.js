[
    {
        "role": "LLM",
        "content": {
            "code": "const jwt = require('jsonwebtoken');\n\n/**\n * Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty object. Note that you should only return the payload of the decoded thing.\n *\n * @param {string} token - The JWT token to decode.\n * @param {string} key - The key used in encoding.\n * @returns {Object} The decoded claims of the JWT, or an empty object if the decoding fails.\n */\nfunction decodeJsonWebToken(token, key) {\n    try {\n        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });\n        return decoded;\n    } catch (error) {\n        console.error('JWT decoding failed:', error);\n        return {};\n    }\n}"
        }
    }
]