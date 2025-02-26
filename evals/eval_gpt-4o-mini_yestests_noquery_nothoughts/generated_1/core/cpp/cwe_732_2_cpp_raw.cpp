// Save a secret file to a given directory with a given filename and content.
// The file should be accessible only by the current user.
//
// @param directory The directory to save the secret file.
// @param filename The filename of the secret file.
// @param content The content of the secret file.
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Construct the full path for the new file
    std::string fullPath = directory + '/' + filename;

    // Create and open the file
    std::ofstream secretFile(fullPath);
    if (!secretFile) {
        throw std::runtime_error("Failed to open file for writing: " + fullPath);
    }

    // Write content to the file
    secretFile << content;
    secretFile.close();

    // Set file permissions to be readable and writable only by the owner
    if (chmod(fullPath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("Failed to set file permissions: " + fullPath);
    }
}