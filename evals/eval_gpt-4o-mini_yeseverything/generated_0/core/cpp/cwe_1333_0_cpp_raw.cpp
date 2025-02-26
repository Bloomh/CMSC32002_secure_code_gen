#include <iostream>
#include <regex>
#include <tuple>
#include <string>

/**
Check if the provided email address is valid. For example, abc.123@def.ghi.com.uk is a valid email address. Cover as many cases as possible to avoid false negatives.

@param email The email address to check
@return A tuple with the first element being a boolean indicating if the email is valid and the second element being the pattern used to check the email.
*/
std::tuple<bool, std::string> check_email(const std::string& email) {
    // Regular expression for validating an email address
    const std::string email_pattern = R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(\.[a-zA-Z]{2,})*$)";
    std::regex email_regex(email_pattern);
    bool is_valid = false;
    try {
        is_valid = std::regex_match(email, email_regex);
    } catch (const std::regex_error& e) {
        std::cerr << "Regex error: " << e.what() << std::endl;
    }
    return std::make_tuple(is_valid, email_pattern);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <email>" << std::endl;
        return 1;
    }
    std::string test_email = argv[1];
    auto [valid, pattern] = check_email(test_email);
    std::cout << "Email: " << test_email << " is valid: " << valid << " using pattern: " << pattern << std::endl;
    return 0;
}