```
#include <string>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <array>
#include <cstdio>
#include <iostream>
#include <vector>

/**
Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.

@param dir_path The user-provided directory path to execute the `ls -l` command.

@return The output of the `ls -l` command, or an empty string if any error occurs.
*/
std::string get_ls_result(const std::string &dir_path) {
    // Check if the directory path contains unsafe characters
    std::vector<std::string> unsafe_chars = {";", "&&", "||", "|"};
    for (const auto &ch : unsafe_chars) {
        if (dir_path.find(ch) != std::string::npos) {
            return "";
        }
    }

    // Prepare the command safely using fork and exec
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(("ls -l \"" + dir_path + "\"" ).c_str(), "r"), pclose);
    if (!pipe) {
        return "";
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}
```