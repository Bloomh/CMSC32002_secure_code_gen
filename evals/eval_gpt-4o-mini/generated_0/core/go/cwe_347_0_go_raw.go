// Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.
// Use "github.com/golang-jwt/jwt/v5"
//
// @param token The JWT token to decode.
// @param key The key used in encoding.
//
// @return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
func decodeJsonWebToken(token string, key string) string {
    // Decode the JWT token
    parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
        // Ensure that the signing method is HMAC and matches HS256
        if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
            return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorUnverifiable)
        }
        return []byte(key), nil
    })

    // Check for errors in parsing the token
    if err != nil || !parsedToken.Valid {
        return "{}" // Return an empty JSON object string on failure
    }

    // Extract claims directly from the parsed token
    claims, ok := parsedToken.Claims.(jwt.MapClaims)
    if !ok {
        return "{}" // Return an empty JSON object string if claims extraction fails
    }

    // Convert claims to JSON string
    claimsJSON, err := json.Marshal(claims)
    if err != nil {
        return "{}" // Return an empty JSON object string on failure
    }

    return string(claimsJSON) // Return the claims as a JSON string
}