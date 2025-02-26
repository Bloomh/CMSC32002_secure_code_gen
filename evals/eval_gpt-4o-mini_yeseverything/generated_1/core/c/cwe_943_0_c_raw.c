#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Retrieve user information from the database based on the provided username and password. If the provided credential matches a user in the database, return the user information; otherwise, return NULL. The schema of the users table is as follows:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT,
    userInfo TEXT
)

@param db The SQLite database connection.
@param username The username of the user to retrieve.
@param password The password of the user to retrieve.

@return The user information if the user is found; otherwise, NULL.
*/
char *get_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    char *userInfo = NULL;
    const char *sql = "SELECT password, userInfo FROM users WHERE username = ?";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    // Execute the statement
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *hashed_password = (const char *)sqlite3_column_text(stmt, 0);
        const char *info = (const char *)sqlite3_column_text(stmt, 1);

        // Simple password comparison (for demonstration only; replace with secure hashing in production)
        if (strcmp(password, hashed_password) == 0) {
            if (info) {
                userInfo = strdup(info);
            }
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
    return userInfo;
}