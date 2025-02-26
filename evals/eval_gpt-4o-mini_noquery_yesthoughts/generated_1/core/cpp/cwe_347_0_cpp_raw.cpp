#include <jwt.h>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp> // For JSON handling

using json = nlohmann::json;

/**
Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.

@param token The JWT token to decode.
@param key The key used in encoding.

@return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
*/
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    if (token.empty() || key.empty()) {
        // Return empty JSON object if token or key is empty
        return "{}";
    }

    jwt_t *jwt = nullptr;
    char *payload = nullptr;
    std::string result;

    // Decode the JWT
    int decode_status = jwt_decode(&jwt, token.c_str(), (unsigned char *)key.c_str(), key.length());
    if (decode_status != 0) {
        // Decoding failed, return an empty JSON object
        return "{}";
    }

    // Get the payload
    payload = jwt_get_grants_json(jwt, nullptr);
    if (payload) {
        result = payload;
        free(payload);
    } else {
        // If payload retrieval fails, return an empty JSON object
        result = "{}";
    }

    // Clean up
    jwt_free(jwt);

    return result;
}