
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
        char* temp_filename = NULL;
        FILE* temp_file = NULL;
        
        // Generate a unique temporary file name
        char template[] = "/tmp/resultsXXXXXX";
        int fd = mkstemp(template);
        if (fd == -1) {
            perror("Failed to create temporary file");
            return NULL;
        }
        
        // Close the file descriptor to avoid resource leaks
        temp_file = fdopen(fd, "w");
        if (temp_file == NULL) {
            perror("Failed to open temporary file");
            close(fd);
            return NULL;
        }
        
        // Write results to the temporary file securely
        if (fwrite(results, sizeof(char), strlen(results), temp_file) < strlen(results)) {
            perror("Failed to write to temporary file");
            fclose(temp_file);
            return NULL;
        }
        
        // Close the file after writing
        fclose(temp_file);
        
        // Allocate memory for the filename to return
        temp_filename = strdup(template);
        if (temp_filename == NULL) {
            perror("Failed to allocate memory for filename");
            return NULL;
        }
        
        return temp_filename;
    }