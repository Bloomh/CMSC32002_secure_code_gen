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
    // Validate inputs
    if (token == NULL || key == NULL) {
        return "{\"error\": \"Invalid input\"}";
    }

    jwt_t *jwt = NULL;
    char *json_claims = NULL;

    // Decode the JWT
    if (jwt_decode(&jwt, token, key, 0) != 0) {
        // Decoding failed, return an error message
        return "{\"error\": \"Invalid token\"}";
    }

    // Get the claims as JSON
    json_claims = jwt_get_grants_json(jwt, NULL); // NULL to get all claims
    if (json_claims == NULL) {
        // If getting grants fails, free jwt and return an error message
        jwt_free(jwt);
        return "{\"error\": \"Failed to get claims\"}";
    }

    // Free the jwt structure
    jwt_free(jwt);

    return json_claims;
}