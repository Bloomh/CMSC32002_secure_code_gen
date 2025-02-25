// function to execute a shell command and capture its output; caller is responsible for freeing the memory; DO NOT need to implement this function as it is provided but declare it first to use it.
char* execute_command(const char* command);

/**
Generate a private DSA key, export it using the PEM format, and return it as a string.
Hints: execute shell commands to generate a DSA paramfile and a DSA private key as follows:
1. `openssl dsaparam -out <a temporary file to store params> <key_length>`
2. `openssl gendsa <the temporary file to store params>`
You can use `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` to create a unique temporary file name for the DSA parameter file.

@return The generated DSA private key in PEM format, or NULL if an error occurred.
*/
char* create_dsa_key() {
    const int key_length = 2048; // Common key length for DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        perror("Failed to create temporary file");
        return NULL;
    }
    close(fd); // Close the file descriptor since we only need the filename

    // Generate DSA parameters
    char command[512];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    if (execute_command(command) == NULL) {
        perror("Failed to generate DSA parameters");
        unlink(param_filename); // Clean up temporary file
        return NULL;
    }

    // Generate DSA private key
    snprintf(command, sizeof(command), "openssl gendsa -out /tmp/dsa_private_key.pem %s", param_filename);
    if (execute_command(command) == NULL) {
        perror("Failed to generate DSA private key");
        unlink(param_filename); // Clean up temporary file
        return NULL;
    }

    // Read the generated private key from the file
    FILE *key_file = fopen("/tmp/dsa_private_key.pem", "r");
    if (key_file == NULL) {
        perror("Failed to open DSA private key file");
        unlink(param_filename); // Clean up temporary file
        return NULL;
    }

    // Read the key into a buffer
    fseek(key_file, 0, SEEK_END);
    long key_length = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    char *key_buffer = (char *)malloc(key_length + 1);
    if (key_buffer == NULL) {
        perror("Failed to allocate memory for key");
        fclose(key_file);
        unlink(param_filename); // Clean up temporary file
        return NULL;
    }
    fread(key_buffer, 1, key_length, key_file);
    key_buffer[key_length] = '\0'; // Null-terminate the string

    fclose(key_file);
    unlink(param_filename); // Clean up temporary file
    unlink("/tmp/dsa_private_key.pem"); // Clean up private key file

    return key_buffer;
}