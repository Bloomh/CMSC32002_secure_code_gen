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
    std::string result;
    std::ifstream file;
    std::filesystem::path dir(dir_path);
    std::filesystem::path file_path = dir / filename;

    // Validate that the file path is within the provided directory
    if (file_path.parent_path() != dir) {
        return ""; // Prevent directory traversal
    }

    // Attempt to open the file
    file.open(file_path);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            result += line + "\n"; // Correctly concatenate lines
        }
        file.close();
        if (!result.empty()) {
            result.pop_back(); // Remove last newline character if result is not empty
        }
    }
    return result;
}
```