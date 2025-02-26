// Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.
// Use "github.com/golang-jwt/jwt/v5"
//
// @param token The JWT token to decode.
// @param key The key used in encoding.
//
// @return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
func decodeJsonWebToken(token string, key string) string {
    claims := &jwt.MapClaims{}
    // Parse the token
    parsedToken, err := jwt.ParseWithClaims(token, claims, func(token *jwt.Token) (interface{}, error) {
        // Ensure that the algorithm is what we expect
        if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
            return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorSignatureInvalid)
        }
        return []byte(key), nil
    })

    // Check for parsing errors
    if err != nil || !parsedToken.Valid {
        return "{}"
    }

    // Return the claims as a JSON object string
    claimsJson, err := json.Marshal(claims)
    if err != nil {
        return "{}"
    }
    return string(claimsJson)
}