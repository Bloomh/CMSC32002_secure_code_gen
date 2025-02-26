#include <jwt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

/**
Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.

@param token The JWT token to decode.
@param key The key used in encoding.

@return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
*/
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char* json_output = NULL;

    // Decode the JWT using the provided key
    if (jwt_decode(&jwt, token, key, strlen(key)) != 0) {
        // If decoding fails, return an empty JSON object
        return strdup("{}");
    }

    // Convert the decoded JWT claims to a JSON string
    json_output = json_dumps(jwt_get_claims(jwt), JSON_COMPACT);

    // Clean up
    jwt_free(jwt);

    return json_output;
}