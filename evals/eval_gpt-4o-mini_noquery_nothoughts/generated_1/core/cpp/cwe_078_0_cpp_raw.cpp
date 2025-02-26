```
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <regex>

/**
Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.

@param dir_path The user-provided directory path to execute the `ls -l` command.

@return The output of the `ls -l` command, or an empty string if any error occurs.
*/
std::string get_ls_result(const std::string &dir_path) {
    // Validate the directory path to prevent command injection
    std::regex path_regex(R"(^[A-Za-z0-9/_-]+$)");
    if (!std::regex_match(dir_path, path_regex)) {
        return ""; // Invalid path format
    }

    std::string command = "ls -l " + dir_path;
    std::array<char, 128> buffer;
    std::string result;

    // Use popen to execute the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Failed to open pipe
    }

    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}
```