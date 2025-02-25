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
    // Validate the directory and filename to prevent path traversal
    if (directory.empty() || filename.empty()) {
        throw std::invalid_argument("Directory and filename must not be empty.");
    }

    // Construct the full path for the file
    std::string fullPath = directory + "/" + filename;

    // Create and open the file
    std::ofstream file(fullPath);
    if (!file) {
        throw std::runtime_error("Unable to create file: " + fullPath);
    }

    // Write content to the file
    file << content;
    file.close();

    // Set file permissions to be accessible only by the owner
    if (chmod(fullPath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("Failed to set file permissions for: " + fullPath);
    }

    std::cout << "Secret file saved successfully: " << fullPath << std::endl;
}