package main

import (
    "database/sql"
    "log"
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
    var userInfo string
    
    // Prepare the SQL statement to prevent SQL injection
    stmt, err := db.Prepare("SELECT userInfo FROM users WHERE username = ? AND password = ?")
    if err != nil {
        log.Println("Error preparing statement:", err)
        return ""
    }
    defer stmt.Close()
    
    // Execute the query with the provided username and password
    err = stmt.QueryRow(username, password).Scan(&userInfo)
    if err != nil {
        if err == sql.ErrNoRows {
            return "" // No user found
        }
        log.Println("Error querying user:", err)
        return ""
    }
    
    return userInfo
}