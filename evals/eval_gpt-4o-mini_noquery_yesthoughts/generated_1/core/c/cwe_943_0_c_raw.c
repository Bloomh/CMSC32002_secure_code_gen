#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
    const char *sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // Execute the statement and retrieve userInfo
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *info = (const char *)sqlite3_column_text(stmt, 0);
        if (info) {
            userInfo = malloc(strlen(info) + 1);
            if (userInfo == NULL) {
                fprintf(stderr, "Memory allocation failed: %s\n", strerror(errno));
                sqlite3_finalize(stmt);
                return NULL;
            }
            strcpy(userInfo, info);
        }
    } else {
        fprintf(stderr, "No user found with the provided credentials.\n");
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    return userInfo;
}