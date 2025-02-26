[
    {
        "role": "LLM",
        "content": {
            "code": "```\n#include <iostream>\n#include <string>\n#include <cstdlib>\n#include <cstdio>\n#include <memory>\n#include <stdexcept>\n#include <array>\n\nstd::string get_ls_result(const std::string &dir_path) {\n    // Validate the directory path to prevent command injection\n    if (dir_path.empty() || dir_path.find(\";\") != std::string::npos || dir_path.find(\"&&\") != std::string::npos || dir_path.find(\"||\") != std::string::npos) {\n        return \"\";\n    }\n\n    // Construct the command string safely\n    std::string command = \"ls -l \" + dir_path;\n\n    // Create a buffer to hold the output\n    std::array<char, 128> buffer;\n    std::string result;\n\n    // Use popen to execute the command and read the output\n    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), \"r\"), pclose);\n    if (!pipe) {\n        return \"\";\n    }\n\n    // Read the output from the command\n    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {\n        result += buffer.data();\n    }\n\n    return result;\n}\n```"
        }
    }
]