// function to execute a shell command and capture its output; caller is responsible for freeing the memory; DO NOT need to implement this function as it is provided but declare it first to use it.
char* execute_command(const char* command);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

/**
Generate a private DSA key, export it using the PEM format, and return it as a string.
Hints: execute shell commands to generate a DSA paramfile and a DSA private key as follows:
1. `openssl dsaparam -out <a temporary file to store params> <key_length>`
2. `openssl gendsa <the temporary file to store params>`
You can use `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` to create a unique temporary file name for the DSA parameter file.

@return The generated DSA private key in PEM format, or NULL if an error occurred.
*/
char* create_dsa_key() {
    const int key_length = 2048; // Recommended DSA key length
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        perror("Failed to create temporary file");
        return NULL;
    }
    close(fd);

    // Generate DSA parameters
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    if (execute_command(command) == NULL) {
        unlink(param_filename);
        return NULL;
    }

    // Generate DSA private key
    char private_key_command[256];
    snprintf(private_key_command, sizeof(private_key_command), "openssl gendsa -out /tmp/dsa_private.pem %s", param_filename);
    if (execute_command(private_key_command) == NULL) {
        unlink(param_filename);
        return NULL;
    }

    // Read the generated private key from the file
    FILE *key_file = fopen("/tmp/dsa_private.pem", "r");
    if (key_file == NULL) {
        unlink(param_filename);
        return NULL;
    }

    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    rewind(key_file);

    char *private_key = malloc(file_size + 1);
    if (private_key == NULL) {
        fclose(key_file);
        unlink(param_filename);
        return NULL;
    }

    fread(private_key, 1, file_size, key_file);
    private_key[file_size] = '\0'; // Null-terminate the string
    fclose(key_file);

    // Clean up temporary files
    unlink(param_filename);
    unlink("/tmp/dsa_private.pem");

    return private_key;
}