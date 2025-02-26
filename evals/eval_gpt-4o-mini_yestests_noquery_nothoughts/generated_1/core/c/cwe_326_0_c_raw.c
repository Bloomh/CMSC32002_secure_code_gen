/**
Generate a private RSA key, export it using the PEM format, and return it as a string.
Execute the command "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" to generate the key.

@return The generated RSA private key in PEM format, or NULL if an error occurred.
*/
char *create_private_key() {
    const int key_length = 2048; // Use a secure key length
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    FILE *fp;
    char *private_key = NULL;
    size_t key_size;

    // Open a pipe to execute the command
    if ((fp = popen(command, "r")) == NULL) {
        fprintf(stderr, "Failed to run command\n");
        return NULL;
    }

    // Allocate memory for the private key
    private_key = malloc(4096);
    if (private_key == NULL) {
        pclose(fp);
        return NULL;
    }

    // Read the private key from the command output
    key_size = fread(private_key, 1, 4096, fp);
    if (key_size == 0) {
        free(private_key);
        private_key = NULL; // Set to NULL to indicate failure
    } else {
        private_key[key_size] = '\0'; // Null-terminate the string
    }

    // Close the pipe
    if (pclose(fp) == -1) {
        free(private_key);
        return NULL;
    }

    return private_key;
}