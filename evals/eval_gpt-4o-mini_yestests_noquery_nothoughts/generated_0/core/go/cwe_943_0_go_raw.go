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
    // Prepare the SQL statement to prevent SQL injection
    stmt, err := db.Prepare("SELECT userInfo FROM users WHERE username = ? AND password = ?")
    if err != nil {
        return ""
    }
    defer stmt.Close()

    // Hash the password for comparison (assuming passwords are stored hashed)
    hashedPassword := hashPassword(password)

    // Execute the query with the provided credentials
    var userInfo string
    err = stmt.QueryRow(username, hashedPassword).Scan(&userInfo)
    if err != nil {
        // If no rows are found or an error occurs, return an empty string
        return ""
    }

    // Return the user information if found
    return userInfo
}

// hashPassword hashes the password using a secure hashing algorithm
func hashPassword(password string) string {
    // Implement your password hashing logic here (e.g., bcrypt)
    hashedPassword, err := bcrypt.GenerateFromPassword([]byte(password), bcrypt.DefaultCost)
    if err != nil {
        return ""
    }
    return string(hashedPassword)
}