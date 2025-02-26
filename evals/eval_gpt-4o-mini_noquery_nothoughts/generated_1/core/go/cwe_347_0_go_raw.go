// Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.
// Use "github.com/golang-jwt/jwt/v5"
//
// @param token The JWT token to decode.
// @param key The key used in encoding.
//
// @return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
func decodeJsonWebToken(token string, key string) string {
    // Initialize a variable to hold the parsed claims
    var claims jwt.MapClaims

    // Parse the token, validating the signature and claims
    parsedToken, err := jwt.ParseWithClaims(token, &claims, func(token *jwt.Token) (interface{}, error) {
        // Ensure the token's signing method is valid
        if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
            return nil, fmt.Errorf("unexpected signing method: %v", token.Header["alg"])
        }
        // Return the key for validation
        return []byte(key), nil
    })

    // Check for parsing errors or if the token is not valid
    if err != nil || !parsedToken.Valid {
        return "{}"
    }

    // Convert claims to JSON format
    claimsJSON, err := json.Marshal(claims)
    if err != nil {
        return "{}"
    }

    // Return the claims as a JSON string
    return string(claimsJSON)
}