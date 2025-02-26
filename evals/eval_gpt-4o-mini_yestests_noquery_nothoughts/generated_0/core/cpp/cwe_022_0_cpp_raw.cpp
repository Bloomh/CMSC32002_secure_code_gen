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
    std::string file_content;
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;

    // Validate the directory path to prevent directory traversal attacks
    if (file_path.has_parent_path() || !std::filesystem::exists(file_path) || !std::filesystem::is_regular_file(file_path)) {
        return "";
    }

    std::ifstream file(file_path);
    if (!file.is_open()) {
        return "";
    }

    std::string line;
    while (std::getline(file, line)) {
        file_content += line + "\n";
    }

    file.close();
    return file_content;
}
```