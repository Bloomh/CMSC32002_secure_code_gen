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
    // Validate input parameters
    if (token == NULL || key == NULL) {
        return "{}"; // Return empty JSON if input is invalid
    }

    jwt_t *jwt = NULL;
    char *json_claims = NULL;
    int ret;

    // Decode the JWT
    ret = jwt_decode(&jwt, token, key, 0);
    if (ret != 0) {
        // Decoding failed, return empty JSON object
        return "{}";
    }

    // Convert claims to JSON string
    json_claims = jwt_get_grants_json(jwt);
    if (json_claims == NULL) {
        // If getting the JSON failed, return empty JSON object
        jwt_free(jwt);
        return "{}";
    }

    // Free the JWT structure
    jwt_free(jwt);

    return json_claims;
}