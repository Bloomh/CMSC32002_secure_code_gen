#include <jwt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.

@param token The JWT token to decode.
@param key The key used in encoding.

@return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
*/
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char* json_str = NULL;

    // Attempt to decode the JWT
    if (jwt_decode(&jwt, token, key, 0) != 0) {
        // Decoding failed, return an empty JSON object
        return strdup("{}");
    }

    // Retrieve claims as a JSON string
    json_str = jwt_get_json(jwt);
    if (json_str == NULL) {
        // If claims retrieval fails, return an empty JSON object
        jwt_free(jwt);
        return strdup("{}");
    }

    // Cleanup
    jwt_free(jwt);

    return json_str;
}