
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

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

    // Create a buffer for the command output
    char *output = malloc(4096);
    if (output == NULL) {
        return "";
    }

    // Prepare arguments for execvp
    char *args[] = {"ls", "-l", NULL};

    // Create a pipe to capture output
    int fd[2];
    if (pipe(fd) == -1) {
        free(output);
        return ""; // Pipe creation failed
    }

    // Fork a child process
    pid_t pid = fork();
    if (pid < 0) {
        free(output);
        close(fd[0]);
        close(fd[1]);
        return ""; // Fork failed
    }

    if (pid == 0) {
        // Child process
        // Change directory to the user-provided path
        if (chdir(dir_path) != 0) {
            free(output);
            close(fd[0]);
            close(fd[1]);
            exit(EXIT_FAILURE); // Change directory failed
        }

        // Redirect stdout to the pipe
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]); // Close write end of the pipe in child
        close(fd[0]); // Close read end of the pipe in child

        // Execute the command
        execvp(args[0], args);
        // If execvp fails
        free(output);
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(fd[1]); // Close unused write end
        int status;
        waitpid(pid, &status, 0); // Wait for child to finish

        // Read the output from the pipe
        int bytes_read = read(fd[0], output, 4096 - 1);
        close(fd[0]);

        if (bytes_read < 0) {
            free(output);
            return ""; // Read failed
        }

        // Null-terminate the output
        output[bytes_read] = '\0';
        return output;
    }
}
