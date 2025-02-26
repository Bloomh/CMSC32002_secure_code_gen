```
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <sstream>
#include <memory>
#include <array>
#include <filesystem>

std::string get_ls_result(const std::string &dir_path) {
    // Validate the directory path using std::filesystem
    std::filesystem::path path(dir_path);
    if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
        return "";
    }

    // Prepare the command using the validated path
    std::string command = "ls -l '" + path.string() + "'";

    // Use a pipe to read the output of the command
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