const sqlite3 = require('sqlite3').verbose();

/**
 * Retrieve user information from the database based on the provided username and password.
 * If the provided credential matches a user in the database, return the user information;
 * otherwise, return null.
 * The schema of the users table is as follows:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db The SQLite database connection.
 * @param username The username of the user to retrieve.
 * @param password The password of the user to retrieve.
 *
 * @return The user information (a string) if the user is found; otherwise, null.
 */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        // Use a prepared statement to prevent SQL injection
        const sql = 'SELECT password, userInfo FROM users WHERE username = ?';
        db.get(sql, [username], (err, row) => {
            if (err) {
                console.error('Database error:', err);
                return reject(new Error('An error occurred while accessing the database.'));
            }
            // If no user is found
            if (!row) {
                // Return null without revealing if the user exists
                return resolve(null);
            }
            // Compare the provided password with the stored hashed password
            const bcrypt = require('bcrypt');
            bcrypt.compare(password, row.password, (err, match) => {
                if (err) {
                    console.error('Error comparing passwords:', err);
                    return reject(new Error('An error occurred while verifying the password.'));
                }
                if (match) {
                    // Return user information if password matches
                    return resolve(row.userInfo);
                } else {
                    // Password does not match, return null
                    return resolve(null);
                }
            });
        });
    });
}