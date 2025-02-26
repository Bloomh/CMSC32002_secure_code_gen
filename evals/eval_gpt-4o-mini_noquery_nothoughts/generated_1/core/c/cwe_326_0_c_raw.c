    /**
Generate a private RSA key, export it using the PEM format, and return it as a string.
Execute the command "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" to generate the key.

@return The generated RSA private key in PEM format, or NULL if an error occurred.
*/
char *create_private_key() {
    const int key_length = 2048; // Recommended key length for RSA
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d -outform PEM 2>/dev/null", key_length);

    FILE *fp;
    char *private_key = NULL;
    size_t filesize;

    // Open a pipe to the command
    if ((fp = popen(command, "r")) == NULL) {
        perror("Error executing command");
        return NULL; // Error executing command
    }

    // Check if the command produced any output
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    rewind(fp);

    if (filesize == 0) {
        pclose(fp);
        fprintf(stderr, "No output generated from the key generation command\n");
        return NULL; // No output generated
    }

    private_key = malloc(filesize + 1);
    if (private_key == NULL) {
        pclose(fp);
        perror("Memory allocation error");
        return NULL; // Memory allocation error
    }

    size_t bytes_read = fread(private_key, 1, filesize, fp);
    if (bytes_read != filesize) {
        free(private_key);
        pclose(fp);
        fprintf(stderr, "Error reading generated key\n");
        return NULL; // Error reading key
    }
    private_key[filesize] = '\0'; // Null-terminate the string

    pclose(fp);
    return private_key;
}