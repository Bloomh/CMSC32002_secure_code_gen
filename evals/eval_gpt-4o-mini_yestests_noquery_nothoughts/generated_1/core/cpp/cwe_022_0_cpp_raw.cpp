    /**
Given a user-provided directory path and a filename, read the file from the directory and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string.

@param filename The name of the file to read, requested by a user.
@param dir_path The path of the directory where the file is located.

@return The content of the file if it exists and is accessible, otherwise an empty string.
*/
std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // Ensure the directory path is safe and does not contain any traversal sequences
    std::string safe_dir_path = dir_path;
    if (safe_dir_path.find("..") != std::string::npos || safe_dir_path.find("/.") != std::string::npos || safe_dir_path.find("\\.") != std::string::npos) {
        return ""; // Return empty string for unsafe directory paths
    }

    // Construct the full file path
    std::string file_path = safe_dir_path + "/" + filename;

    // Initialize a string to hold the file content
    std::string content;
    std::ifstream file(file_path);

    // Check if the file can be opened
    if (!file.is_open()) {
        return ""; // Return empty string if file cannot be opened
    }

    // Read the file content
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n"; // Append each line to content
    }

    // Close the file
    file.close();

    // Remove the trailing newline character if content is not empty
    if (!content.empty()) {
        content.pop_back(); // Remove last '\n'
    }

    return content;
}