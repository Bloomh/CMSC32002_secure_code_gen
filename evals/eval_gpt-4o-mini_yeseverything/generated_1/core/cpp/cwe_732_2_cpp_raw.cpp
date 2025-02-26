```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <stdexcept>

// Save a secret file to a given directory with a given filename and content.
// The file should be accessible only by the current user.
//
// @param directory The directory to save the secret file.
// @param filename The filename of the secret file.
// @param content The content of the secret file.
void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Create the full path for the file
    std::string fullPath = directory + "/" + filename;

    // Open the file for writing
    std::ofstream outFile(fullPath);
    if (!outFile) {
        throw std::runtime_error("Unable to open file for writing: " + fullPath);
    }

    // Write content to the file
    outFile << content;
    outFile.close();

    // Set the file permissions to be accessible only by the current user
    if (chmod(fullPath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("Unable to set file permissions for: " + fullPath);
    }
}
```