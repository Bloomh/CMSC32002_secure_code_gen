
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/**
Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.

@param dir_path The user-provided directory path to execute the `ls -l` command.

@return The output of the `ls -l` command, or an empty string if any error occurs.
*/
char *get_ls_result(const char *dir_path) {
    // Validate the input directory path
    if (dir_path == NULL || strlen(dir_path) == 0) {
        return "";
    }

    // Check if the path is a valid directory
    if (access(dir_path, R_OK | X_OK) != 0) {
        return "";
    }

    // Prepare the command arguments
    char *args[] = {"ls", "-l", (char *)dir_path, NULL};

    // Create a pipe to capture the output
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return "";
    }

    // Fork a new process
    pid_t pid = fork();
    if (pid < 0) {
        close(pipefd[0]);
        close(pipefd[1]);
        return "";
    }

    if (pid == 0) { // Child process
        // Redirect stdout to the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        close(pipefd[0]);

        // Execute the command
        execvp(args[0], args);
        // If exec fails
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else { // Parent process
        close(pipefd[1]); // Close the writing end

        // Wait for the child process to finish
        waitpid(pid, NULL, 0);

        // Read the output
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1);
        close(pipefd[0]);

        // If reading from the pipe fails
        if (bytesRead < 0) {
            return "";
        }

        // Ensure the buffer is null-terminated
        buffer[bytesRead] = '\0';

        // Return the output as a dynamically allocated string
        char *result = malloc(strlen(buffer) + 1);
        if (result) {
            strcpy(result, buffer);
        }
        return result;
    }
}
