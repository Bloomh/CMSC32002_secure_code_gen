package main

import (
    "encoding/json"
    "github.com/golang-jwt/jwt/v5"
)

// Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.
// Use "github.com/golang-jwt/jwt/v5".
//
// @param token The JWT token to decode.
// @param key The key used in encoding.
//
// @return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
func decodeJsonWebToken(token string, key string) string {
    claims := &jwt.MapClaims{}
    // Parse the token
    parsedToken, err := jwt.ParseWithClaims(token, claims, func(token *jwt.Token) (interface{}, error) {
        // Validate the algorithm
        if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
            return nil, jwt.ErrSignatureInvalid // Return an error for invalid signing method
        }
        return []byte(key), nil
    })

    // Check if there was an error in parsing the token
    if err != nil || !parsedToken.Valid {
        return "{}" // Return empty JSON object string on failure
    }

    // Convert claims to JSON
    claimsJSON, err := json.Marshal(claims)
    if err != nil {
        return "{}" // Return empty JSON object string in case of JSON marshalling error
    }

    return string(claimsJSON) // Return the decoded claims as a JSON string
}