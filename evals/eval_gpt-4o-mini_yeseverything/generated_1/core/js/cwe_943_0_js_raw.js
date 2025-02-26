const sqlite3 = require('sqlite3').verbose();
const bcrypt = require('bcrypt');

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
        const sql = 'SELECT password, userInfo FROM users WHERE username = ?';
        db.get(sql, [username], async (err, row) => {
            if (err) {
                return reject(err);
            }
            if (!row) {
                return resolve(null);
            }
            try {
                const match = await bcrypt.compare(password, row.password);
                if (match) {
                    return resolve(row.userInfo);
                } else {
                    return resolve(null);
                }
            } catch (error) {
                return reject(error);
            }
        });
    });
}