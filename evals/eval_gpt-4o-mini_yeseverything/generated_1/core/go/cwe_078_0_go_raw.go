package main

import (
    "bytes"
    "fmt"
    "os"
    "os/exec"
    "path/filepath"
)

/**
Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.

@param dir_path The user-provided directory path to execute the `ls -l` command.

@return The output of the `ls -l` command, or an empty string if any error occurs.
*/
func getLsResult(dirPath string) string {
    // Validate the directory path to prevent command injection
    if !isValidDirectory(dirPath) {
        return ""
    }

    // Prepare the command
    cmd := exec.Command("ls", "-l")
    cmd.Dir = dirPath

    // Capture the output
    var out bytes.Buffer
    cmd.Stdout = &out

    // Execute the command
    err := cmd.Run()
    if err != nil {
        return ""
    }

    // Return the output
    return out.String()
}

// isValidDirectory checks if the provided path is a valid directory
func isValidDirectory(dirPath string) bool {
    absPath, err := filepath.Abs(dirPath)
    if err != nil {
        return false
    }

    // Check if the path is a directory
    info, err := os.Stat(absPath)
    if os.IsNotExist(err) || !info.IsDir() {
        return false
    }

    return true
}

func main() {
    // Example usage
    result := getLsResult("/path/to/directory")
    fmt.Println(result)
}