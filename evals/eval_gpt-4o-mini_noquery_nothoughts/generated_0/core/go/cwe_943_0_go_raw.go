
    /*
Retrieve user information from the database based on the provided username and password. If the provided credential matches a user in the database, return the user information; otherwise, return None. The schema of the users table is as follows:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

Use "github.com/mattn/go-sqlite3".

@param db The SQLite database connection.
@param username The username of the user to retrieve.
@param password The password of the user to retrieve.

@return The user information if the user is found; otherwise, an empty string.
*/
func getUser(db *sql.DB, username, password string) string {
    var userInfo string
    var storedHash string
    // Use a prepared statement to prevent SQL injection
    stmt, err := db.Prepare("SELECT userInfo, password FROM users WHERE username = ?")
    if err != nil {
        log.Println("Error preparing statement:", err)
        return ""
    }
    defer stmt.Close()

    // Execute the statement with provided parameters
    err = stmt.QueryRow(username).Scan(&userInfo, &storedHash)
    if err != nil {
        if err == sql.ErrNoRows {
            return ""
        }
        log.Println("Error querying user info:", err)
        return ""
    }

    // Validate the provided password against the stored hash
    if isPasswordValid(storedHash, password) {
        return userInfo
    }
    return ""
}

// Securely compare passwords using bcrypt
func isPasswordValid(storedHash, password string) bool {
    // Use bcrypt to compare hashed passwords securely
    err := bcrypt.CompareHashAndPassword([]byte(storedHash), []byte(password))
    return err == nil
}