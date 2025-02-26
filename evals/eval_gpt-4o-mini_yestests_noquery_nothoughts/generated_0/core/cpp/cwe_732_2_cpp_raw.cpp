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
    // Construct the full path for the file
    std::filesystem::path filePath = std::filesystem::path(directory) / filename;

    // Ensure the directory exists
    if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory)) {
        throw std::runtime_error("Directory does not exist or is not a directory.");
    }

    // Create and open the file
    std::ofstream outFile(filePath);
    if (!outFile) {
        throw std::runtime_error("Failed to create the file.");
    }

    // Write the content to the file
    outFile << content;
    outFile.close();

    // Set file permissions to be accessible only by the current user
    int result = chmod(filePath.c_str(), S_IRUSR | S_IWUSR);
    if (result != 0) {
        throw std::runtime_error("Failed to set file permissions.");
    }

    std::cout << "Secret file saved successfully at: " << filePath << std::endl;
}