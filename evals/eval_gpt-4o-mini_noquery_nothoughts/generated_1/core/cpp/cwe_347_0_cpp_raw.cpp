#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp>
#include <iostream>
#include <stdexcept>

using json = nlohmann::json;

/**
Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.

@param token The JWT token to decode.
@param key The key used in encoding.

@return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
*/
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt;
    char *json_str = nullptr;

    // Initialize JWT library
    if (jwt_new(&jwt) != 0) {
        std::cerr << "Failed to create JWT object" << std::endl;
        return "{}"; // Return empty JSON object on failure
    }

    // Decode the JWT
    if (jwt_decode(jwt, token.c_str(), (unsigned char*)key.c_str(), key.length()) != 0) {
        std::cerr << "JWT decoding failed" << std::endl;
        jwt_free(jwt);
        return "{}"; // Return empty JSON object on failure
    }

    // Get the claims as a JSON string
    json_str = jwt_get_grants_json(jwt);
    if (json_str == nullptr) {
        std::cerr << "Failed to get claims JSON" << std::endl;
        jwt_free(jwt);
        return "{}"; // Return empty JSON object on failure
    }

    std::string claims_json(json_str);

    // Free the JWT object
    jwt_free(jwt);
    free(json_str);

    return claims_json;
}