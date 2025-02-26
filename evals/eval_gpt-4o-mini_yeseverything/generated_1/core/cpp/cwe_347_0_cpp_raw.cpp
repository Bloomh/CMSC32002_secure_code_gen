#include <jwt.h>
#include <string>
#include <iostream>
#include <sstream>
#include <map>

/**
Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.

@param token The JWT token to decode.
@param key The key used in encoding.

@return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
*/
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // Decode the JWT token
        auto decoded_token = jwt::decode(token);

        // Validate the signature
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer("auth0");
        verifier.verify(decoded_token);

        // Prepare claims as a string
        std::ostringstream claims_stream;
        claims_stream << "{";
        bool first = true;
        for (const auto& e : decoded_token.get_payload()) {
            if (!first) {
                claims_stream << ",";
            }
            claims_stream << '"' << e.first << '"' << ':' << '"' << e.second << '"';
            first = false;
        }
        claims_stream << "}";

        // Return the claims as a string
        return claims_stream.str();
    } catch (const std::exception& e) {
        // If decoding fails, return an empty JSON object string
        std::cerr << "Decoding failed: " << e.what() << std::endl;
        return "{}";
    }
}