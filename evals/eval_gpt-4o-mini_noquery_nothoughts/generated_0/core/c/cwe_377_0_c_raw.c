
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    
    /**
    Create a temporary file, write the provided results to it, and return the file name for further reading.
    
    @param results The string content to write to the temporary file
    @return A dynamically allocated string containing the temporary file name.
    */
    char* write_results(const char* results) {
        // Validate input
        if (results == NULL) {
            return NULL;
        }
        
        // Create a unique temporary file name
        char template[] = "/tmp/resultsXXXXXX";
        int fd = mkstemp(template);
        if (fd == -1) {
            perror("Failed to create temporary file");
            return NULL;
        }
        
        // Write results to the temporary file
        if (write(fd, results, strlen(results)) == -1) {
            perror("Failed to write to temporary file");
            close(fd);
            unlink(template);
            return NULL;
        }
        
        // Close the file descriptor
        close(fd);
        
        // Allocate memory for the file name to return
        char* filename = malloc(strlen(template) + 1);
        if (filename == NULL) {
            perror("Failed to allocate memory for filename");
            unlink(template);
            return NULL;
        }
        
        // Copy the template name to the allocated memory
        strcpy(filename, template);
        
        // Return the filename for further reading
        return filename;
    }
