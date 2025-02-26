#include <jwt.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <cstring>

/**
Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.

@param token The JWT token to decode.
@param key The key used in encoding.

@return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
*/
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt = nullptr;
    unsigned char *payload = nullptr;

    // Decode the JWT
    if (jwt_decode(&jwt, token.c_str(), reinterpret_cast<const unsigned char*>(key.c_str()), key.length()) != 0) {
        // Decoding failed, return an empty JSON object
        return "{}";
    }

    // Verify the signature
    if (jwt_verify(jwt, reinterpret_cast<const unsigned char*>(key.c_str()), key.length()) != 0) {
        jwt_free(jwt);
        return "{}"; // Invalid signature, return empty JSON object
    }

    // Extract the payload from the JWT
    payload = jwt_get_payload(jwt);
    if (payload == nullptr) {
        jwt_free(jwt);
        return "{}";
    }

    // Convert the payload to a JSON string
    std::string json_string(reinterpret_cast<const char*>(payload));
    jwt_free(jwt);

    // Return the JSON string
    return json_string;
}