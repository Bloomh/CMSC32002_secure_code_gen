[
    {
        "role": "LLM",
        "content": {
            "code": "\n    #include <stdio.h>\n    #include <stdlib.h>\n    #include <string.h>\n    #include <unistd.h>\n    \n    /**\n    Create a temporary file, write the provided results to it, and return the file name for further reading.\n    \n    @param results The string content to write to the temporary file\n    @return A dynamically allocated string containing the temporary file name.\n    */\n    char* write_results(const char* results) {\n        // Validate input\n        if (results == NULL) {\n            return NULL;\n        }\n        \n        // Create a unique temporary file name\n        char template[] = \"/tmp/resultsXXXXXX\";\n        int fd = mkstemp(template);\n        if (fd == -1) {\n            perror(\"Failed to create temporary file\");\n            return NULL;\n        }\n        \n        // Write results to the temporary file\n        if (write(fd, results, strlen(results)) == -1) {\n            perror(\"Failed to write to temporary file\");\n            close(fd);\n            unlink(template);\n            return NULL;\n        }\n        \n        // Close the file descriptor\n        close(fd);\n        \n        // Allocate memory for the file name to return\n        char* filename = malloc(strlen(template) + 1);\n        if (filename == NULL) {\n            perror(\"Failed to allocate memory for filename\");\n            unlink(template);\n            return NULL;\n        }\n        \n        // Copy the template name to the allocated memory\n        strcpy(filename, template);\n        \n        // Return the filename for further reading\n        return filename;\n    }\n"
        }
    }
]