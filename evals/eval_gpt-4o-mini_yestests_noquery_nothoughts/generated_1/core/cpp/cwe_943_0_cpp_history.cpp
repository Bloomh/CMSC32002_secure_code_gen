[
    {
        "role": "LLM",
        "content": {
            "code": "#include <sqlite3.h>\n#include <string>\n#include <iostream>\n#include <stdexcept>\n\nstd::string getUser(sqlite3* db, const std::string& username, const std::string& password) {\n    sqlite3_stmt* stmt;\n    std::string sql = \"SELECT userInfo FROM users WHERE username = ? AND password = ?\";\n\n    // Prepare the SQL statement to prevent SQL injection\n    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {\n        throw std::runtime_error(\"Failed to prepare statement: \" + std::string(sqlite3_errmsg(db)));\n    }\n\n    // Bind the parameters\n    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);\n    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);\n\n    std::string userInfo;\n    // Execute the statement and retrieve the result\n    if (sqlite3_step(stmt) == SQLITE_ROW) {\n        const char* info = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));\n        userInfo = info ? info : \"\";\n    }\n\n    // Finalize the statement to clean up\n    sqlite3_finalize(stmt);\n\n    return userInfo;\n}"
        }
    }
]