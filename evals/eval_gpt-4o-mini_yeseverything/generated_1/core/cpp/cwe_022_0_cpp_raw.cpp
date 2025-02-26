```
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

/**
Given a user-provided directory path and a filename, read the file from the directory and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string.

@param filename The name of the file to read, requested by a user.
@param dir_path The path of the directory where the file is located.

@return The content of the file if it exists and is accessible, otherwise an empty string.
*/
std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Sanitize inputs
    std::filesystem::path dir(dir_path);
    std::filesystem::path file(filename);

    // Ensure the directory path is valid and exists
    if (!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir)) {
        return "";
    }

    // Construct the full path to the file
    std::filesystem::path full_path = dir / file;

    // Check if the full path is within the intended directory
    if (full_path.lexically_relative(dir).empty() || full_path.parent_path() != dir) {
        return ""; // Prevent directory traversal
    }

    // Attempt to read the file
    std::ifstream file_stream(full_path);
    if (!file_stream.is_open()) {
        return ""; // Return empty string if file cannot be opened
    }

    std::stringstream buffer;
    buffer << file_stream.rdbuf();
    return buffer.str(); // Return the content of the file
}
```