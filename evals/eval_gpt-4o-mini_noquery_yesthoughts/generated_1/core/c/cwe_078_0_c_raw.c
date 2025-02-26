```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#define BUFFER_SIZE 4096

/**
Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.

@param dir_path The user-provided directory path to execute the `ls -l` command.

@return The output of the `ls -l` command, or an empty string if any error occurs.
*/
char *get_ls_result(const char *dir_path) {
    // Validate the directory path
    if (dir_path == NULL || strlen(dir_path) == 0) {
        return "";
    }

    struct stat statbuf;
    if (stat(dir_path, &statbuf) != 0 || !S_ISDIR(statbuf.st_mode)) {
        return "";
    }

    // Check for invalid characters in the directory path
    for (size_t i = 0; i < strlen(dir_path); i++) {
        if (dir_path[i] == ';' || dir_path[i] == '&' || dir_path[i] == '|' || dir_path[i] == '>' || dir_path[i] == '<') {
            return ""; // Invalid character detected
        }
    }

    // Prepare the command safely
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ls -l '%s' 2>&1", dir_path);

    // Open a pipe to execute the command
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "";
    }

    // Read the output of the command
    char *result = malloc(BUFFER_SIZE);
    if (result == NULL) {
        pclose(fp);
        return "";
    }
    size_t total_length = 0;
    size_t bytes_read;

    while ((bytes_read = fread(result + total_length, 1, BUFFER_SIZE - total_length - 1, fp)) > 0) {
        total_length += bytes_read;
        if (total_length >= BUFFER_SIZE - 1) {
            break;
        }
    }

    // Null-terminate the result
    result[total_length] = '\0';

    // Close the pipe
    pclose(fp);

    return result;
}
```