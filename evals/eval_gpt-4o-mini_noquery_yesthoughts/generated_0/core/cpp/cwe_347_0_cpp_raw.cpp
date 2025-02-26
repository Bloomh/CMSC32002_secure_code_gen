#include <jwt.h>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp> // Include for JSON handling

using json = nlohmann::json;

/**
Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.

@param token The JWT token to decode.
@param key The key used in encoding.

@return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
*/
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // Decode the JWT and validate the signature using the key
        auto jwt_obj = jwt::decode(token);
        auto verifier = jwt::verify().allow_algorithm(jwt::algorithm::hs256{key}).with_issuer("auth0");
        verifier.verify(jwt_obj);
        // Return the claims as a JSON string
        json claims = jwt_obj.payload();
        return claims.dump();
    } catch (const std::exception& e) {
        // Log the error (for production, consider a proper logging mechanism)
        std::cerr << "JWT decoding failed: " << e.what() << std::endl;
        // Return an empty JSON object string on failure
        return "{}";
    }
}