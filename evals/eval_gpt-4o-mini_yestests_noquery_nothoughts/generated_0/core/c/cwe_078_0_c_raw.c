```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.

@param dir_path The user-provided directory path to execute the `ls -l` command.

@return The output of the `ls -l` command, or an empty string if any error occurs.
*/
char *get_ls_result(const char *dir_path) {
    if (dir_path == NULL) return "";

    // Validate the directory path
    char *safe_dir_path = realpath(dir_path, NULL);
    if (safe_dir_path == NULL) return "";

    // Prepare the command securely
    char command[256];
    snprintf(command, sizeof(command), "ls -l '%s'", safe_dir_path);

    // Execute the command and capture the output
    FILE *fp;
    char *result = NULL;
    size_t size = 0;

    fp = popen(command, "r");
    if (fp == NULL) {
        free(safe_dir_path);
        return "";
    }

    // Read the output
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t len = strlen(buffer);
        char *new_result = realloc(result, size + len + 1);
        if (new_result == NULL) {
            free(result);
            result = NULL;
            break;
        }
        result = new_result;
        strcpy(result + size, buffer);
        size += len;
    }

    // Clean up
    pclose(fp);
    free(safe_dir_path);

    return result ? result : "";
}
```