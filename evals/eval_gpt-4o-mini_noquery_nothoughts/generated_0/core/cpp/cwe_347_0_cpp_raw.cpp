#include <jwt.h>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp> // Include JSON library for handling JSON data

using json = nlohmann::json;

/**
Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.

@param token The JWT token to decode.
@param key The key used in encoding.

@return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
*/
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // Decode the JWT using the provided key
        auto decoded_jwt = jwt::decode(token,
            jwt::params::algorithms({"HS256"}),
            jwt::params::secret(key)
        );

        // Extract claims into a JSON object
        json claims = json::object();
        for (const auto& pair : decoded_jwt.payload()) {
            claims[pair.first] = pair.second;
        }

        // Return the claims as a JSON string
        return claims.dump();
    } catch (const jwt::token_verification_exception& e) {
        // Handle specific JWT verification exceptions
        std::cerr << "JWT verification failed: " << e.what() << std::endl;
        return "{}";
    } catch (const std::exception& e) {
        // In case of any other error, return an empty JSON object string
        std::cerr << "JWT decoding failed: " << e.what() << std::endl;
        return "{}";
    }
}