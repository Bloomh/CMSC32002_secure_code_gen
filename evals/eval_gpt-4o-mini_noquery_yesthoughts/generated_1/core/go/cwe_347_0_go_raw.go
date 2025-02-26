// Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.
// Use "github.com/golang-jwt/jwt/v5"
//
// @param token The JWT token to decode.
// @param key The key used in encoding.
//
// @return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
func decodeJsonWebToken(token string, key string) string {
    claims := jwt.MapClaims{}
    // Parse the token
    t, err := jwt.ParseWithClaims(token, claims, func(token *jwt.Token) (interface{}, error) {
        // Verify the signing method is what we expect
        if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
            log.Println("Invalid signing method detected.")
            return nil, fmt.Errorf("invalid signing method")
        }
        return []byte(key), nil
    })

    // Check if parsing the token was successful
    if err != nil || !t.Valid {
        log.Println("Error decoding JWT: invalid token or claims.")
        return "{}"
    }

    // Convert claims to JSON
    claimsJSON, err := json.Marshal(claims)
    if err != nil {
        log.Println("Error marshaling claims to JSON.")
        return "{}"
    }

    return string(claimsJSON)
}