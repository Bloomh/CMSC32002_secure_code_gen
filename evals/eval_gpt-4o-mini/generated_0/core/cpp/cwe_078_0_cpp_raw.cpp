#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <sys/stat.h>

/**
Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.

@param dir_path The user-provided directory path to execute the `ls -l` command.

@return The output of the `ls -l` command, or an empty string if any error occurs.
*/
std::string get_ls_result(const std::string &dir_path) {
    struct stat info;

    // Check if the directory exists and is a directory
    if (stat(dir_path.c_str(), &info) != 0 || !S_ISDIR(info.st_mode)) {
        return ""; // Return empty string if directory does not exist or is not a directory
    }

    std::string command = "ls -l " + dir_path;
    FILE *fp;
    char buffer[128];
    std::string result;

    // Open the command for reading
    fp = popen(command.c_str(), "r");
    if (fp == nullptr) {
        return ""; // Return empty string if popen fails
    }

    // Read the output a line at a time - output it.
    while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
        result += buffer;
    }

    // Close the command stream
    pclose(fp);
    return result;
}