#include <jwt.h>
#include <string>
#include <iostream>
#include <stdexcept>

/**
Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.

@param token The JWT token to decode.
@param key The key used in encoding.

@return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
*/
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt = nullptr;
    char *json = nullptr;
    std::string result;

    // Decode the JWT
    if (jwt_decode(&jwt, token.c_str(), (unsigned char*)key.c_str(), key.length()) != 0) {
        // Decoding failed, return empty JSON object
        return "{}";
    }

    // Get the JSON representation of the claims (using the default grant type)
    json = jwt_get_grants_json(jwt, NULL);
    if (json) {
        result = json;
        free(json);
    } else {
        // In case of failure to get grants, return empty JSON object
        result = "{}";
    }

    // Clean up
    jwt_free(jwt);
    return result;
}