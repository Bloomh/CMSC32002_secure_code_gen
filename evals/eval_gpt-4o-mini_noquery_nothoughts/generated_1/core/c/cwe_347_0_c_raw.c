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
    char* decoded_claims = NULL;
    jwt_t *jwt = NULL;

    // Decode the JWT
    int r = jwt_decode(&jwt, token, key, 0);
    if (r != 0) {
        // Decoding failed, return an empty JSON object
        return strdup("{}");
    }

    // Get the claims as a JSON string
    const char *claims = jwt_get_grants_json(jwt, NULL);
    if (claims == NULL) {
        // If getting claims fails, free jwt and return an empty JSON object
        jwt_free(jwt);
        return strdup("{}");
    }

    // Validate claims length to prevent buffer overflow
    size_t claims_length = strlen(claims);
    if (claims_length == 0 || claims_length > 1024) {
        // Handle invalid claims securely
        jwt_free(jwt);
        return strdup("{}");
    }

    // Store the claims in a dynamically allocated string
    decoded_claims = (char*)malloc(claims_length + 1);
    if (decoded_claims == NULL) {
        // Memory allocation failed, free jwt and return an empty JSON object
        jwt_free(jwt);
        return strdup("{}");
    }
    strcpy(decoded_claims, claims);
    jwt_free(jwt);

    return decoded_claims;
}