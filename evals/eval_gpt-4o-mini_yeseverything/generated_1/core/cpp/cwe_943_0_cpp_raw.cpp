#include <sqlite3.h>
#include <string>
#include <iostream>

std::string getUser(sqlite3* db, const std::string& username, const std::string& password) {
    sqlite3_stmt* stmt;
    std::string userInfo;
    const char* sql = "SELECT userInfo FROM users WHERE username = ? AND password = ?";

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return "";
    }

    // Bind parameters to prevent SQL injection
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    // Execute the statement and retrieve user information
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* info = sqlite3_column_text(stmt, 0);
        userInfo = reinterpret_cast<const char*>(info);
    }

    // Finalize the statement to release resources
    sqlite3_finalize(stmt);

    return userInfo;
}