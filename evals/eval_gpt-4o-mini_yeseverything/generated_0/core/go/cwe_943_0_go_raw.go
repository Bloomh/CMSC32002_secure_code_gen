package main

import (
    "database/sql"
    "log"
    "golang.org/x/crypto/bcrypt"
    _ "github.com/mattn/go-sqlite3"
)

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
    var storedPassword string
    var userInfo string

    // Prepare the SQL statement to prevent SQL injection
    stmt, err := db.Prepare("SELECT password, userInfo FROM users WHERE username = ?")
    if err != nil {
        log.Println("Error preparing statement:", err)
        return ""
    }
    defer stmt.Close()

    // Execute the statement with the provided username
    err = stmt.QueryRow(username).Scan(&storedPassword, &userInfo)
    if err != nil {
        // If no rows were found, return an empty string
        if err == sql.ErrNoRows {
            return ""
        }
        log.Println("Error querying user:", err)
        return ""
    }

    // Compare the provided password with the stored hashed password
    err = bcrypt.CompareHashAndPassword([]byte(storedPassword), []byte(password))
    if err != nil {
        // Password does not match
        return ""
    }

    // Return user information if the password is correct
    return userInfo
}