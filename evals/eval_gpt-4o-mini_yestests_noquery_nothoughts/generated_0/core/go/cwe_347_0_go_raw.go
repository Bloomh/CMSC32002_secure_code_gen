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
    claims := &jwt.MapClaims{}
    // Parse the token and validate it
    parsedToken, err := jwt.ParseWithClaims(token, claims, func(token *jwt.Token) (interface{}, error) {
        // Ensure the token's signing method is HS256
        if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
            return nil, nil // Return nil instead of an error to avoid leaking information
        }
        return []byte(key), nil
    })

    // Check for errors in parsing
    if err != nil || !parsedToken.Valid {
        return "{}"
    }

    // Convert claims to JSON
    claimsJSON, err := json.Marshal(claims)
    if err != nil {
        return "{}"
    }

    return string(claimsJSON)
}