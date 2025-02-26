// Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.
// Use "github.com/golang-jwt/jwt/v5"
//
// @param token The JWT token to decode.
// @param key The key used in encoding.
//
// @return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
func decodeJsonWebToken(token string, key string) string {
    // Parse the JWT token
    parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
        // Ensure that the algorithm used to sign the token is HS256
        if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
            log.Println("Invalid signing method")
            return nil, jwt.ErrSignatureInvalid
        }
        return []byte(key), nil
    })

    if err != nil || !parsedToken.Valid {
        log.Println("Failed to decode JWT:", err)
        return "{}" // Return an empty JSON object string on failure
    }

    // Extract claims
    claims, ok := parsedToken.Claims.(jwt.MapClaims)
    if !ok {
        log.Println("Claims are not of type MapClaims")
        return "{}" // Return an empty JSON object string if claims are invalid
    }

    claimsJSON, err := json.Marshal(claims)
    if err != nil {
        log.Println("Error marshaling claims:", err)
        return "{}" // Return an empty JSON object string if marshaling fails
    }

    return string(claimsJSON)
}