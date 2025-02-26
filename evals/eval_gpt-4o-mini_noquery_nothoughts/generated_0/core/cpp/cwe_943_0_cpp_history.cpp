[
    {
        "role": "LLM",
        "content": {
            "code": "#include <sqlite3.h>\n#include <string>\n#include <iostream>\n#include <stdexcept>\n\n/*\nRetrieve user information from the database based on the provided username and password. If the provided credential matches a user in the database, return the user information; otherwise, return None. The schema of the users table is as follows:\n\nCREATE TABLE users (\n    username TEXT PRIMARY KEY,\n    password TEXT,\n    userInfo TEXT\n)\n\nUse \"github.com/mattn/go-sqlite3\".\n\n@param db The SQLite database connection.\n@param username The username of the user to retrieve.\n@param password The password of the user to retrieve.\n\n@return The user information if the user is found; otherwise, an empty string.\n*/\nstd::string getUser(sqlite3* db, const std::string& username, const std::string& password) {\n    sqlite3_stmt* stmt;\n    const char* sql = \"SELECT userInfo FROM users WHERE username = ? AND password = ?\";\n\n    // Prepare the SQL statement\n    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {\n        throw std::runtime_error(\"Failed to prepare statement: \" + std::string(sqlite3_errmsg(db)));\n    }\n\n    // Bind parameters to prevent SQL injection\n    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);\n    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);\n\n    std::string userInfo;\n    if (sqlite3_step(stmt) == SQLITE_ROW) {\n        const char* info = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));\n        userInfo = info ? info : \"\";\n    }\n\n    // Finalize the statement to release resources\n    sqlite3_finalize(stmt);\n\n    return userInfo;\n}"
        }
    }
]