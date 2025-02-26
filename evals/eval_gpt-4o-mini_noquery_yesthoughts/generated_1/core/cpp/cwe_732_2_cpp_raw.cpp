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

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Validate the directory
    if (directory.empty() || filename.empty()) {
        throw std::invalid_argument("Directory and filename must not be empty.");
    }

    // Construct the full path
    std::string filePath = directory + '/' + filename;

    // Create the file and write content
    std::ofstream outFile(filePath);
    if (!outFile) {
        throw std::runtime_error("Failed to create file: " + filePath);
    }
    outFile << content;
    outFile.close();

    // Set file permissions to be accessible only by the current user
    if (chmod(filePath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("Failed to set file permissions for: " + filePath);
    }

    std::cout << "Secret file saved successfully to " << filePath << std::endl;
}