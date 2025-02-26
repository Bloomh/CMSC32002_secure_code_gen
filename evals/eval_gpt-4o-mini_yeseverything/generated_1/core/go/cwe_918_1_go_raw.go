    
    func getURLForQuery(apiURL, userID string) *string {
        // Validate userID: it should not be empty and should match expected patterns
        if userID == "" {
            return nil
        }

        // Sanitize userID (for example, allow only alphanumeric characters)
        for _, char := range userID {
            if !(('a' <= char && char <= 'z') || ('A' <= char && char <= 'Z') || ('0' <= char && char <= '9')) {
                return nil
            }
        }

        // Construct the final URL
        finalURL := apiURL + "/" + userID
        return &finalURL
    }