```
import (
    "os/exec"
    "path/filepath"
    "strings"
)

/**
Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.

@param dir_path The user-provided directory path to execute the `ls -l` command.

@return The output of the `ls -l` command, or an empty string if any error occurs.
*/
func getLsResult(dirPath string) string {
    // Validate the directory path to prevent command injection
    if !isValidPath(dirPath) {
        return ""
    }

    // Prepare the command
    cmd := exec.Command("ls", "-l", dirPath)

    // Get the output
    output, err := cmd.Output()
    if err != nil {
        return ""
    }

    return strings.TrimSpace(string(output))
}

// isValidPath checks if the provided path is a valid directory path
func isValidPath(path string) bool {
    // Clean the path to avoid traversal attacks
    cleanPath := filepath.Clean(path)
    // Check if the cleaned path is a directory
    info, err := os.Stat(cleanPath)
    return err == nil && info.IsDir()
}
```