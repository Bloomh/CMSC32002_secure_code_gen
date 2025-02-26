#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

char* create_dsa_key() {
    // Create a unique temporary file name for DSA parameters
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        perror("Failed to create temporary file");
        return NULL;
    }
    close(fd);

    // Define the key length
    const int key_length = 2048;

    // Generate DSA parameters
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Clean up the temporary file
        return NULL;
    }

    // Generate DSA private key
    char private_key_command[256];
    snprintf(private_key_command, sizeof(private_key_command), "openssl gendsa -out /dev/stdout %s", param_filename);
    char* private_key = execute_command(private_key_command);

    // Clean up the temporary file
    unlink(param_filename);

    return private_key;
}