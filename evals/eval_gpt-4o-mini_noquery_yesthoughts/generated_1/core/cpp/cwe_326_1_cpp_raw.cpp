// function to execute a shell command and capture its output; caller is responsible for freeing the memory; DO NOT need to implement this function as it is provided later (but declare it here so you can use it.
std::string execute_command(const std::string& command);

/**
Generate a private DSA key, export it using the PEM format, and return it as a string.
Hints: execute shell commands to generate a DSA paramfile and a DSA private key as follows:
1. `openssl dsaparam -out <a temporary file to store params> <key_length>`
2. `openssl gendsa <the temporary file to store params>`
You can use `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` to create a unique temporary file name for the DSA parameter file.

@return The generated DSA private key in PEM format, or an empty string if an error occurred.
*/
std::string create_dsa_key() {
    // Define key length
    const int key_length = 2048;

    // Create a temporary file for DSA parameters
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // Failed to create temporary file
    }
    close(fd);

    // Generate DSA parameters
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    std::string param_result = execute_command(param_command);
    if (!param_result.empty()) {
        unlink(param_filename); // Clean up on error
        return ""; // Error in generating parameters
    }

    // Generate DSA private key
    std::string key_command = "openssl gendsa -out /dev/stdout " + std::string(param_filename);
    std::string private_key = execute_command(key_command);

    // Clean up temporary file
    unlink(param_filename);

    return private_key;
}