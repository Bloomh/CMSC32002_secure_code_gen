#include <jwt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.

@param token The JWT token to decode.
@param key The key used in encoding.

@return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
*/
char* decode_json_web_token(const char* token, const char* key) {
    // Validate input parameters
    if (token == NULL || key == NULL) {
        return strdup("{}"); // Return empty JSON object on NULL input
    }

    jwt_t *jwt = NULL;
    char* json_claims = NULL;
    int ret = jwt_decode(&jwt, token, key, 0);

    // Check for decoding errors
    if (ret != 0) {
        return strdup("{}"); // Decoding failed, return empty JSON object
    }

    // Retrieve JSON claims
    json_claims = jwt_get_json(jwt);
    if (json_claims == NULL) {
        jwt_free(jwt);
        return strdup("{}"); // Failed to get JSON claims, return empty JSON object
    }

    // Duplicate the string for return
    char* result = strdup(json_claims);
    jwt_free(jwt); // Free JWT structure
    return result; // Return the decoded claims
}