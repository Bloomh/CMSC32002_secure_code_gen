#include <jwt.h>
#include <string>
#include <json/json.h> // Assuming a JSON library is available
#include <iostream>

/**
Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.

@param token The JWT token to decode.
@param key The key used in encoding.

@return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
*/
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    // Check if the key is empty
    if (key.empty()) {
        std::cerr << "Error: The key provided is empty." << std::endl;
        return "{}"; // Return empty JSON object on failure
    }

    jwt::decoded_jwt decoded;
    try {
        // Decode the token
        decoded = jwt::decode(token);

        // Verify the signature
        auto verifier = jwt::verify().allow_algorithm(jwt::algorithm::hs256{key}).with_issuer("auth0");
        verifier.verify(decoded);

        // Extract claims
        Json::Value claims;
        for (const auto& e : decoded.get_payload()) {
            claims[e.first] = e.second;
        }

        // Convert claims to string
        Json::StreamWriterBuilder writer;
        return Json::writeString(writer, claims);
    } catch (const jwt::token_verification_exception& e) {
        // Log token verification exceptions
        std::cerr << "Token verification failed: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        // Log any other exceptions
        std::cerr << "Exception while decoding JWT: " << e.what() << std::endl;
    }
    return "{}"; // Return empty JSON object on failure
}