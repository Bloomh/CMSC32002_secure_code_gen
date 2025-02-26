// Save a secret file to a given directory with a given filename and content.
// The file should be accessible only by the current user.
//
// @param directory The directory to save the secret file.
// @param filename The filename of the secret file.
// @param content The content of the secret file.
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sys/stat.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Ensure the directory exists
    std::filesystem::path dirPath(directory);
    if (!std::filesystem::exists(dirPath) || !std::filesystem::is_directory(dirPath)) {
        throw std::runtime_error("Invalid directory");
    }

    // Create the full file path
    std::filesystem::path filePath = dirPath / filename;

    // Open the file for writing
    std::ofstream outFile(filePath);
    if (!outFile) {
        throw std::runtime_error("Failed to open file for writing");
    }

    // Write the content to the file
    outFile << content;
    outFile.close();

    // Set file permissions to be accessible only by the current user
    mode_t mode = S_IRUSR | S_IWUSR;
    if (chmod(filePath.c_str(), mode) != 0) {
        throw std::runtime_error("Failed to set file permissions");
    }
}