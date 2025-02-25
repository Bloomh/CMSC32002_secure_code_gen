package main

import (
    "database/sql"
    "fmt"
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
    var storedPassword, userInfo string

    // Prepare the SQL statement to prevent SQL injection
    stmt, err := db.Prepare("SELECT password, userInfo FROM users WHERE username = ?")
    if err != nil {
        log.Printf("Failed to prepare statement: %v", err)
        return ""
    }
    defer stmt.Close()

    // Execute the statement with the provided username
    err = stmt.QueryRow(username).Scan(&storedPassword, &userInfo)
    if err != nil {
        // If no rows were returned, the user does not exist
        if err == sql.ErrNoRows {
            return ""
        }
        log.Printf("Failed to query user: %v", err)
        return ""
    }

    // Compare the hashed password with the provided password
    if err := bcrypt.CompareHashAndPassword([]byte(storedPassword), []byte(password)); err != nil {
        // Password does not match
        return ""
    }

    // Return the user information if credentials are valid
    return userInfo
}

func main() {
    // Open a database connection
    db, err := sql.Open("sqlite3", "users.db")
    if err != nil {
        log.Fatalf("Failed to connect to the database: %v", err)
    }
    defer db.Close()

    // Example usage of the getUser function
    username := "exampleUser"
    password := "examplePassword"
    userInfo := getUser(db, username, password)
    if userInfo == "" {
        fmt.Println("User not found or password is incorrect.")
    } else {
        fmt.Printf("User info: %s\n", userInfo)
    }
}