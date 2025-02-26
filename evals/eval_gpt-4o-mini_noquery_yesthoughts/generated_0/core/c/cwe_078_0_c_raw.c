```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

/**
Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.

@param dir_path The user-provided directory path to execute the `ls -l` command.

@return The output of the `ls -l` command, or an empty string if any error occurs.
*/
char *get_ls_result(const char *dir_path) {
    // Validate the input directory path
    if (dir_path == NULL || strlen(dir_path) == 0 || strlen(dir_path) > PATH_MAX) {
        return "";
    }

    // Create a pipe to capture the output
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        return "";
    }

    pid_t pid = fork();
    if (pid < 0) {
        return "";
    } else if (pid == 0) {
        // Child process
        close(pipe_fd[0]); // Close read end
        dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipe_fd[1]);

        // Change directory to the user-provided path
        if (chdir(dir_path) == -1) {
            exit(1); // Exit with error if directory change fails
        }

        // Execute the ls -l command
        execlp("ls", "ls", "-l", NULL);
        exit(1); // Exit if execlp fails
    } else {
        // Parent process
        close(pipe_fd[1]); // Close write end
        wait(NULL); // Wait for child process to finish

        // Read the output from the pipe
        char *output = malloc(4096);
        if (output == NULL) {
            return "";
        }

        ssize_t bytes_read = read(pipe_fd[0], output, 4096);
        close(pipe_fd[0]);

        if (bytes_read < 0) {
            free(output);
            return "";
        }

        output[bytes_read] = '\0'; // Null-terminate the string
        return output;
    }
}
```