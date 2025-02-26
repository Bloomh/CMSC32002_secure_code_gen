// Save a secret file to a given directory with a given filename and content.
// The file should be accessible only by the current user.
//
// @param directory The directory to save the secret file.
// @param filename The filename of the secret file.
// @param content The content of the secret file.
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Create the full path for the secret file
    std::string filePath = directory + "/" + filename;

    // Open the file for writing
    std::ofstream outFile(filePath);
    if (!outFile) {
        throw std::runtime_error("Failed to open file for writing: " + filePath);
    }

    // Write content to the file
    outFile << content;
    outFile.close();

    // Set file permissions to be readable/writable only by the owner
    if (chmod(filePath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("Failed to set file permissions: " + filePath);
    }
}