import os
import subprocess

/**
Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.

@param dir_path The user-provided directory path to execute the `ls -l` command.

@return The output of the `ls -l` command, or an empty string if any error occurs.
*/
func getLsResult(dirPath string) string {
    // Validate the directory path
    if dirPath == "" {
        return ""
    }
    // Check if the directory exists and is indeed a directory
    info, err := os.Stat(dirPath)
    if err != nil || !info.IsDir() {
        return ""
    }

    // Execute the command securely
    cmd := exec.Command("ls", "-l", dirPath)
    output, err := cmd.Output()
    if err != nil {
        return ""
    }

    // Return the sanitized output
    return string(output)
}