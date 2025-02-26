#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char *get_ls_result(const char *dir_path) {
    // Validate the input to prevent command injection
    if (dir_path == NULL || strlen(dir_path) == 0) {
        return "";
    }

    // Create a buffer to hold the command output
    char *output = (char *)malloc(BUFFER_SIZE);
    if (output == NULL) {
        return "";
    }

    // Prepare the arguments for execvp
    char *args[] = {"ls", "-l", (char *)dir_path, NULL};

    // Redirect output to a pipe
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        free(output);
        return "";
    }

    // Fork the process
    pid_t pid = fork();
    if (pid < 0) {
        free(output);
        return "";
    }

    if (pid == 0) {
        // Child process
        dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipe_fd[0]); // Close unused read end
        execvp(args[0], args); // Execute the command
        // If execvp fails
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipe_fd[1]); // Close unused write end
        // Read the command output
        size_t read_size = read(pipe_fd[0], output, BUFFER_SIZE - 1);
        output[read_size] = '\0'; // Null-terminate the string
        close(pipe_fd[0]); // Close read end
        wait(NULL); // Wait for child process to finish
    }

    return output;
}