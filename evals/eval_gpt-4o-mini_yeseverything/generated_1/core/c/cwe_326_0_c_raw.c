char *create_private_key() {
    const int key_length = 2048;  // Recommended key length
    const char *temp_filename = "/tmp/private_key.pem";
    char command[256];
    FILE *file;

    // Generate the private key using OpenSSL command
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d -out %s 2>/dev/null", key_length, temp_filename);
    int result = system(command);

    if (result != 0) {
        return NULL;  // Error in key generation
    }

    // Open the temporary file to read the private key
    file = fopen(temp_filename, "r");
    if (!file) {
        return NULL;  // Error opening the file
    }

    // Read the private key into a string
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *private_key = (char *)malloc(filesize + 1);
    if (!private_key) {
        fclose(file);
        return NULL;  // Memory allocation error
    }

    fread(private_key, 1, filesize, file);
    private_key[filesize] = '\0';  // Null-terminate the string

    fclose(file);

    // Optionally, remove the temporary file for security
    remove(temp_filename);

    return private_key;  // Return the private key in PEM format
}