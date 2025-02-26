#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // Validate the directory path
    if (!std::filesystem::exists(dir_path) || !std::filesystem::is_directory(dir_path)) {
        return ""; // Return empty string if the directory does not exist or is not a directory
    }

    // Prepare the command to execute
    std::string command = "ls -l " + dir_path;

    // Create a buffer to capture the command output
    std::array<char, 128> buffer;
    std::string result;

    // Open a pipe to the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return empty string if pipe could not be opened
    }

    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result; // Return the command output
}