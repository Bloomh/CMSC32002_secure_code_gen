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
#include <unistd.h>

void saveSecretFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Construct the full path for the file
    std::filesystem::path filePath = std::filesystem::path(directory) / filename;

    // Create the directory if it does not exist
    std::filesystem::create_directories(directory);

    // Open the file for writing in binary mode
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    // Write the content to the file
    outFile << content;
    outFile.close();

    // Set the file permissions to be accessible only by the current user
    if (chmod(filePath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        std::cerr << "Error: Could not set file permissions.\n";
    }
    // Verify the file ownership and permissions
    if (chown(filePath.c_str(), getuid(), getgid()) != 0) {
        std::cerr << "Error: Could not set file ownership.\n";
    }
}