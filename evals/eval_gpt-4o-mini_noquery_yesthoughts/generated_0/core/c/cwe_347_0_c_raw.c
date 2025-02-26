#include <jwt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.

@param token The JWT token to decode.
@param key The key used in encoding.

@return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
*/
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char* json_claims = NULL;

    // Decode the JWT
    if (jwt_decode(&jwt, token, (unsigned char*)key, strlen(key)) != 0) {
        // Decoding failed, return an empty JSON object string
        return strdup("{}");
    }

    // Serialize the claims to a JSON string
    json_claims = jwt_get_grants_json(jwt);

    // Check if serialization was successful
    if (json_claims == NULL) {
        // Cleanup and return empty JSON object
        jwt_free(jwt);
        return strdup("{}");
    }

    // Cleanup
    jwt_free(jwt);

    return json_claims;
}