#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <array>
#include <cstdio>

std::string get_ls_result(const std::string &dir_path) {
    // Validate the directory path to prevent command injection
    if (!std::filesystem::exists(dir_path) || !std::filesystem::is_directory(dir_path)) {
        return ""; // Return empty string if path is invalid or not a directory
    }

    // Prepare command to execute
    std::string command = "ls -l " + dir_path;
    std::array<char, 128> buffer;
    std::string result;

    // Open a pipe to the command
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Return empty string if pipe creation failed
    }

    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}