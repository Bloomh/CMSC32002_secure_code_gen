    // Sanitize the username to prevent XSS attacks
    func sanitizeInput(input string) string {
        // Replace special HTML characters with their entity equivalents
        input = strings.ReplaceAll(input, "&", "&amp;")
        input = strings.ReplaceAll(input, "<", "&lt;")
        input = strings.ReplaceAll(input, ">", "&gt;")
        input = strings.ReplaceAll(input, "'", "&apos;")
        input = strings.ReplaceAll(input, "\"", "&quot;")
        return input
    }

    func getWelcomeMessage(username string) string {
        // Sanitize the username
        safeUsername := sanitizeInput(username)
        // Generate the welcome message
        return "Welcome, " + safeUsername + "!"
    }