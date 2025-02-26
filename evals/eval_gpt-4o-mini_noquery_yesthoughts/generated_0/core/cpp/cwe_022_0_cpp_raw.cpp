```
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

/**
 * Given a user-provided directory path and a filename, read the file from the directory and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string.
 *
 * @param filename The name of the file to read, requested by a user.
 * @param dir_path The path of the directory where the file is located.
 *
 * @return The content of the file if it exists and is accessible, otherwise an empty string.
 */
std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Normalize directory path
    std::filesystem::path dir = std::filesystem::canonical(dir_path);
    if (!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir)) {
        return ""; // Return empty string if dir_path is not a valid directory
    }

    // Construct the full file path
    std::filesystem::path file_path = dir / filename;

    // Check if the file path is within the specified directory
    if (file_path.parent_path() != dir) {
        return ""; // Prevent path traversal
    }

    // Attempt to read the file
    std::ifstream file(file_path);
    if (!file.is_open()) {
        return ""; // Return empty string if file cannot be opened
    }

    // Read the content of the file
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n"; // Append each line to content
    }

    return content;
}
```