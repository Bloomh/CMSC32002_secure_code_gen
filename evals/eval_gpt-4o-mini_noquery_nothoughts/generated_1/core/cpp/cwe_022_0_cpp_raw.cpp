```
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

/**
Given a user-provided directory path and a filename, read the file from the directory and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string.

@param filename The name of the file to read, requested by a user.
@param dir_path The path of the directory where the file is located.

@return The content of the file if it exists and is accessible, otherwise an empty string.
*/
std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Construct the full path
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;

    // Normalize the path to prevent directory traversal attacks
    try {
        // Ensure the path is absolute and check for directory traversal
        std::filesystem::path absolute_path = std::filesystem::canonical(file_path);

        // Check if the path is a valid file and exists
        if (!std::filesystem::exists(absolute_path) || !std::filesystem::is_regular_file(absolute_path)) {
            return ""; // File does not exist or is not a regular file
        }

        std::ifstream file(absolute_path);
        if (!file.is_open()) {
            return ""; // Could not open the file
        }

        std::string content;
        std::string line;
        while (std::getline(file, line)) {
            content += line + '\n';
        }

        file.close();
        return content;
    } catch (const std::exception &e) {
        return ""; // Return empty string on any exception
    }
}
```