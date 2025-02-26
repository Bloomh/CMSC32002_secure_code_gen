// Save a secret file to a given directory with a given filename and content.
// The file should be accessible only by the current user.
//
// @param directory The directory to save the secret file.
// @param filename The filename of the secret file.
// @param content The content of the secret file.
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <stdexcept>
#include <filesystem>

void saveSecretFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Validate directory and filename to prevent path traversal
    if (directory.empty() || filename.empty() || filename.find("..") != std::string::npos) {
        throw std::invalid_argument("Invalid directory or filename.");
    }

    // Check if the directory exists
    if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory)) {
        throw std::invalid_argument("Directory does not exist: " + directory);
    }

    // Create the full path for the secret file
    std::filesystem::path fullPath = std::filesystem::path(directory) / filename;

    // Open the file for writing
    std::ofstream outFile(fullPath);
    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + fullPath.string());
    }

    // Write content to the file
    outFile << content;
    outFile.close();

    // Set file permissions to be accessible only by the owner (user)
    if (chmod(fullPath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("Failed to set file permissions: " + fullPath.string());
    }

    std::cout << "Secret file saved successfully: " << fullPath.string() << std::endl;
}