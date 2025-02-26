```cpp
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
    std::regex valid_path_regex(R"(^[\w\-./]+$)");
    if (dir_path.empty() || !std::regex_match(dir_path, valid_path_regex)) {
        return "";
    }

    // Prepare the command to execute
    std::string command = "ls -l \"" + dir_path + "\"";

    // Use a pipe to read the command output
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return "";
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}
```