[
    {
        "role": "LLM",
        "content": {
            "code": "const sqlite3 = require('sqlite3').verbose();\n\n/**\n * Retrieve user information from the database based on the provided username and password.\n * If the provided credential matches a user in the database, return the user information;\n * otherwise, return null.\n * The schema of the users table is as follows:\n *\n * CREATE TABLE users (\n *     username TEXT PRIMARY KEY,\n *     password TEXT,\n *     userInfo TEXT\n * );\n *\n * @param db The SQLite database connection.\n * @param username The username of the user to retrieve.\n * @param password The password of the user to retrieve.\n *\n * @return The user information (a string) if the user is found; otherwise, null.\n */\nfunction getUser(db, username, password) {\n    return new Promise((resolve, reject) => {\n        // Use parameterized query to prevent SQL injection\n        const sql = 'SELECT userInfo FROM users WHERE username = ? AND password = ?';\n        db.get(sql, [username, password], (err, row) => {\n            if (err) {\n                return reject(err);\n            }\n            // Check if user was found and return userInfo or null\n            if (row) {\n                resolve(row.userInfo);\n            } else {\n                resolve(null);\n            }\n        });\n    });\n}"
        }
    }
]