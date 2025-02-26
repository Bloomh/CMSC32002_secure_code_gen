```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/**
Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.

@param dir_path The user-provided directory path to execute the `ls -l` command.

@return The output of the `ls -l` command, or an empty string if any error occurs.
*/
char *get_ls_result(const char *dir_path) {
    // Validate the input directory path to prevent command injection
    if (dir_path == NULL || strlen(dir_path) == 0) {
        return "";
    }

    // Create an array for command arguments
    char *command[] = {"ls", "-l", (char *)dir_path, NULL};

    // Open a pipe to the command using execvp to avoid shell interpretation
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return ""; // Return empty string on pipe error
    }

    pid_t pid = fork();
    if (pid < 0) {
        return ""; // Return empty string on fork error
    } else if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        execvp(command[0], command); // Execute the command
        // If execvp fails
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipefd[1]); // Close write end
        char *output = malloc(1024);
        if (output == NULL) {
            return ""; // Return empty string if memory allocation fails
        }

        // Read the output from the command
        ssize_t total_read = read(pipefd[0], output, 1024);
        if (total_read < 0) {
            free(output);
            return ""; // Return empty string if read fails
        }
        output[total_read] = '\0'; // Null-terminate the string

        // Wait for child process to finish
        wait(NULL);

        return output;
    }
}
```