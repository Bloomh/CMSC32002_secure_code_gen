#include <jwt.h>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

/**
Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.

@param token The JWT token to decode.
@param key The key used in encoding.

@return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
*/
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // Decode the JWT with proper verification of the signature
        auto decoded_jwt = jwt::decode(token,
            jwt::params::algorithms({"HS256"}),
            jwt::params::secret(key)
        );

        // Collect claims into a JSON object
        json claims = json::object();
        for (const auto& claim : decoded_jwt.payload()) {
            claims[claim.first] = claim.second;
        }
        return claims.dump();
    } catch (const std::exception& e) {
        std::cerr << "Decoding failed: " << e.what() << std::endl;
        return "{}";  // Return empty JSON object string on failure
    }
}