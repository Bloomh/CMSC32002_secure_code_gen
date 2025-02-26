```
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // Validate the directory path to prevent command injection
    if (dir_path.empty() || dir_path.find(";") != std::string::npos || dir_path.find("&&") != std::string::npos || dir_path.find("||") != std::string::npos) {
        return "";
    }

    // Construct the command string safely
    std::string command = "ls -l " + dir_path;

    // Create a buffer to hold the output
    std::array<char, 128> buffer;
    std::string result;

    // Use popen to execute the command and read the output
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return "";
    }

    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}
```