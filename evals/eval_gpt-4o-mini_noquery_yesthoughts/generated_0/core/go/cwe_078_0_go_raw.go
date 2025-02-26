```
import (
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
    // Validate the directory path
    if !isValidDirectory(dirPath) {
        return ""
    }

    // Create the command
    cmd := exec.Command("ls", "-l", dirPath)

    // Get the output
    output, err := cmd.Output()
    if err != nil {
        return ""
    }

    return string(output)
}

// isValidDirectory checks if the provided path is a valid directory.
func isValidDirectory(dirPath string) bool {
    // Clean and check if the path is a directory
    absPath, err := filepath.Abs(dirPath)
    if err != nil {
        return false
    }
    info, err := os.Stat(absPath)
    if os.IsNotExist(err) || !info.IsDir() {
        return false
    }
    return true
}
```