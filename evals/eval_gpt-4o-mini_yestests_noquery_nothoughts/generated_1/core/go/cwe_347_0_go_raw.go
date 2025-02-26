// Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.
// Use "github.com/golang-jwt/jwt/v5"
//
// @param token The JWT token to decode.
// @param key The key used in encoding.
//
// @return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
import (
    "encoding/json"
    "github.com/golang-jwt/jwt/v5"
)

func decodeJsonWebToken(token string, key string) string {
    // Parse the token using the key
    parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
        // Ensure that the signing method is HMAC and check for the correct algorithm
        if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
            return nil, jwt.ErrSignatureInvalid
        }
        return []byte(key), nil
    })

    // Check if there was an error during parsing
    if err != nil || !parsedToken.Valid {
        return "{}" // Return an empty JSON object string
    }

    // Extract claims from the token
    claims, ok := parsedToken.Claims.(jwt.MapClaims)
    if !ok || len(claims) == 0 {
        return "{}" // Return an empty JSON object string
    }

    // Convert claims to JSON
    claimsJSON, err := json.Marshal(claims)
    if err != nil {
        return "{}" // Return an empty JSON object string if marshalling fails
    }

    return string(claimsJSON) // Return the claims as a JSON string
}