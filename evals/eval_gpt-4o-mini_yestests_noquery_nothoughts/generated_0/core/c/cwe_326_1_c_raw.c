// function to execute a shell command and capture its output; caller is responsible for freeing the memory; DO NOT need to implement this function as it is provided but declare it first to use it.
char* execute_command(const char* command);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

/**
Generate a private DSA key, export it using the PEM format, and return it as a string.
Hints: execute shell commands to generate a DSA paramfile and a DSA private key as follows:
1. `openssl dsaparam -out <a temporary file to store params> <key_length>`
2. `openssl gendsa <the temporary file to store params>`
You can use `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` to create a unique temporary file name for the DSA parameter file.

@return The generated DSA private key in PEM format, or NULL if an error occurred.
*/
char* create_dsa_key() {
    const int key_length = 2048; // Minimum secure key length
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        perror("Failed to create temporary file");
        return NULL;
    }
    close(fd);

    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    if (execute_command(command) == NULL) {
        unlink(param_filename);
        return NULL;
    }

    snprintf(command, sizeof(command), "openssl gendsa -out /tmp/dsa_private.pem %s", param_filename);
    char* private_key = execute_command(command);
    unlink(param_filename); // Clean up the temporary file

    if (private_key == NULL) {
        return NULL;
    }

    // Check if the private key is valid by ensuring it is in PEM format
    if (strstr(private_key, "-----BEGIN DSA PRIVATE KEY-----") == NULL) {
        free(private_key);
        return NULL;
    }

    // Ensure the key size is valid (2048 bits or more)
    // This requires parsing the key; we assume that the command executed successfully and the key is valid.
    // A more robust implementation would validate this further.

    return private_key;
}