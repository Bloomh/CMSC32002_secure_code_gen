    /**
Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.

@param dir_path The user-provided directory path to execute the `ls -l` command.

@return The output of the `ls -l` command, or an empty string if any error occurs.
*/
char *get_ls_result(const char *dir_path) {
    // Validate the input to prevent command injection
    if (dir_path == NULL || strpbrk(dir_path, "|&;"\"'\$`\n") != NULL) {
        return "";
    }

    // Prepare the command string safely
    char command[512];
    snprintf(command, sizeof(command), "ls -l '%s'", dir_path);

    // Create a pipe to read the command output
    FILE *fp;
    char buffer[128];
    char *result = (char *)malloc(1024 * sizeof(char));
    if (result == NULL) {
        return "";
    }
    result[0] = '\0'; // Initialize result

    // Execute the command
    fp = popen(command, "r");
    if (fp == NULL) {
        free(result);
        return "";
    }

    // Read the output a line at a time - write to result
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Ensure we do not exceed the allocated memory
        if (strlen(result) + strlen(buffer) < 1024) {
            strcat(result, buffer);
        } else {
            break; // Avoid buffer overflow
        }
    }

    // Close the pipe
    pclose(fp);

    return result;
}