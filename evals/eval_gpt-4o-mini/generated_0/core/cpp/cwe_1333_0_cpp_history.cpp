[
    {
        "role": "LLM",
        "content": {
            "code": "```\n#include <regex>\n#include <tuple>\n#include <string>\n\n/**\nCheck if the provided email address is valid. For example, abc.123@def.ghi.com.uk is a valid email address. Cover as many cases as possible to avoid false negatives.\n\n@param email The email address to check\n@return A tuple with the first element being a boolean indicating if the email is valid and the second element being the pattern used to check the email.\n*/\nstd::tuple<bool, std::string> check_email(const std::string& email) {\n    // Regex pattern for validating an email address\n    const std::string pattern = R\"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$)\";\n    std::regex email_regex(pattern);\n\n    // Validate the email address\n    bool is_valid = std::regex_match(email, email_regex);\n    return std::make_tuple(is_valid, pattern);\n}\n```"
        }
    }
]