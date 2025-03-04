```
#include <string>
#include <tuple>
#include <regex>

/**
Check if the provided email address is valid. For example, abc.123@def.ghi.com.uk is a valid email address. Cover as many cases as possible to avoid false negatives.

@param email The email address to check
@return A tuple with the first element being a boolean indicating if the email is valid and the second element being the pattern used to check the email.
*/
std::tuple<bool, std::string> check_email(const std::string& email) {
    // Regular expression for validating an email address
    const std::string email_pattern = R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$)";
    std::regex regex(email_pattern);

    // Check if the email matches the regex pattern
    bool is_valid = std::regex_match(email, regex);

    return std::make_tuple(is_valid, email_pattern);
}
```