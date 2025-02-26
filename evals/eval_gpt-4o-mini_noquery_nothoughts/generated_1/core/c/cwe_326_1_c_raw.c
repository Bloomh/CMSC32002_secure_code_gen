
// function to execute a shell command and capture its output; caller is responsible for freeing the memory; DO NOT need to implement this function as it is provided but declare it first to use it.
char* execute_command(const char* command);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/**
Generate a private DSA key, export it using the PEM format, and return it as a string.
Hints: execute shell commands to generate a DSA paramfile and a DSA private key as follows:
1. `openssl dsaparam -out <a temporary file to store params> <key_length>`
2. `openssl gendsa <the temporary file to store params>`
You can use `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` to create a unique temporary file name for the DSA parameter file.

@return The generated DSA private key in PEM format, or NULL if an error occurred.
*/
char* create_dsa_key() {
    const int key_length = 2048; // Recommended minimum key length for DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);

    if (fd == -1) {
        perror("mkstemp");
        return NULL;
    }
    close(fd);

    // Create DSA parameters
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Clean up temporary file
        return NULL;
    }

    // Generate DSA private key
    char* private_key_command = NULL;
    if (asprintf(&private_key_command, "openssl gendsa -out /tmp/dsa_private.pem %s", param_filename) < 0) {
        unlink(param_filename); // Clean up temporary file
        return NULL;
    }
    if (execute_command(private_key_command) == NULL) {
        free(private_key_command);
        unlink(param_filename); // Clean up temporary file
        return NULL;
    }
    free(private_key_command);

    // Read the generated private key from the file
    FILE* key_file = fopen("/tmp/dsa_private.pem", "r");
    if (!key_file) {
        perror("fopen");
        unlink(param_filename); // Clean up temporary file
        return NULL;
    }

    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);

    if (file_size < 0) {
        fclose(key_file);
        unlink(param_filename); // Clean up temporary file
        return NULL;
    }

    char* key_buffer = (char*)malloc(file_size + 1);
    if (!key_buffer) {
        fclose(key_file);
        unlink(param_filename); // Clean up temporary file
        return NULL;
    }

    fread(key_buffer, 1, file_size, key_file);
    key_buffer[file_size] = '\0'; // Null-terminate the string
    fclose(key_file);

    // Clean up the private key file
    unlink("/tmp/dsa_private.pem");
    unlink(param_filename); // Clean up temporary file

    return key_buffer;
}