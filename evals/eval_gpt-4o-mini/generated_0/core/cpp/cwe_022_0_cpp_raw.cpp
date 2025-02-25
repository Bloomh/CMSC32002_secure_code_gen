#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

// Define a base directory for security purposes
const std::filesystem::path BASE_DIR = "/safe/base/directory";

/**
 * Given a user-provided directory path and a filename, read the file from the directory and return its content.
 * If any error occurs during the file reading process (e.g., file not found, permission error), return an empty string.
 *
 * @param filename The name of the file to read, requested by a user.
 * @param dir_path The path of the directory where the file is located.
 *
 * @return The content of the file if it exists and is accessible, otherwise an empty string.
 */
std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    std::filesystem::path path(dir_path);
    std::filesystem::path full_path = path / filename;
    
    // Ensure the full path is within the base directory
    if (full_path.lexically_normal().string().find(BASE_DIR.string()) != 0) {
        return ""; // Invalid path, return empty string
    }
    
    // Check if the file exists and is a regular file
    if (!std::filesystem::exists(full_path) || !std::filesystem::is_regular_file(full_path)) {
        return ""; // File not found or not a regular file
    }
    
    // Attempt to read the file
    std::ifstream file(full_path);
    if (!file.is_open()) {
        return ""; // File not accessible
    }
    
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n"; // Append line to content
    }
    file.close();
    return content;
}