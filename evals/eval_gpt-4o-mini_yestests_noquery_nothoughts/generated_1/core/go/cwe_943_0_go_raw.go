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
    stmt, err := db.Prepare("SELECT password, userInfo FROM users WHERE username = ?")
    if err != nil {
        log.Fatalf("Error preparing statement: %v", err)
    }
    defer stmt.Close()

    // Execute the statement
    var hashedPassword, userInfo string
    err = stmt.QueryRow(username).Scan(&hashedPassword, &userInfo)
    if err != nil {
        if err == sql.ErrNoRows {
            return "" // User not found
        }
        log.Fatalf("Error querying user: %v", err)
    }

    // Use bcrypt to compare the hashed password with the provided password
    if err := bcrypt.CompareHashAndPassword([]byte(hashedPassword), []byte(password)); err != nil {
        return "" // Password does not match
    }

    // Return user information if credentials are correct
    return userInfo
}