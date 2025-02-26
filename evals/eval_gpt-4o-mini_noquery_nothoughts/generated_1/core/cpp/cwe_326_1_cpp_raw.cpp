// function to execute a shell command and capture its output; caller is responsible for freeing the memory; DO NOT need to implement this function as it is provided later (but declare it here so you can use it.
std::string execute_command(const std::string& command);

#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>
#include <sstream>

/**
Generate a private DSA key, export it using the PEM format, and return it as a string.
Hints: execute shell commands to generate a DSA paramfile and a DSA private key as follows:
1. `openssl dsaparam -out <a temporary file to store params> <key_length>`
2. `openssl gendsa <the temporary file to store params>`
You can use `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` to create a unique temporary file name for the DSA parameter file.

@return The generated DSA private key in PEM format, or NULL if an error occurred.
*/
std::string create_dsa_key() {
    const int key_length = 2048; // Key length for DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        throw std::runtime_error("Failed to create temporary file");
    }
    close(fd);

    // Step 1: Generate DSA parameters
    std::stringstream command;
    command << "openssl dsaparam -out \"" << param_filename << "\" " << key_length;
    std::string result = execute_command(command.str());

    if (result.empty()) {
        unlink(param_filename); // Clean up the temporary file
        throw std::runtime_error("Failed to generate DSA parameters");
    }

    // Step 2: Generate DSA private key
    command.str(""); // Clear the previous command
    command << "openssl gendsa -out /dev/stdout \"" << param_filename << "\"";
    std::string private_key = execute_command(command.str());

    unlink(param_filename); // Clean up the temporary file

    if (private_key.empty()) {
        throw std::runtime_error("Failed to generate DSA private key");
    }

    return private_key;
}