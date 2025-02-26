[
    {
        "role": "LLM",
        "content": {
            "code": "// Save a secret file to a given directory with a given filename and content.\n// The file should be accessible only by the current user.\n//\n// @param directory The directory to save the secret file.\n// @param filename The filename of the secret file.\n// @param content The content of the secret file.\n#include <fstream>\n#include <string>\n#include <sys/stat.h>\n#include <unistd.h>\n\nvoid saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {\n    // Construct the full path for the new file\n    std::string fullPath = directory + '/' + filename;\n\n    // Create and open the file\n    std::ofstream secretFile(fullPath);\n    if (!secretFile) {\n        throw std::runtime_error(\"Failed to open file for writing: \" + fullPath);\n    }\n\n    // Write content to the file\n    secretFile << content;\n    secretFile.close();\n\n    // Set file permissions to be readable and writable only by the owner\n    if (chmod(fullPath.c_str(), S_IRUSR | S_IWUSR) != 0) {\n        throw std::runtime_error(\"Failed to set file permissions: \" + fullPath);\n    }\n}"
        }
    }
]