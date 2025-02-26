// Include necessary headers
#include <string>
#include <regex>
#include <iostream>

/**
Check if the provided target URL string is within the provided domain.
If so, return the target URL for redirect; otherwise, fallback to the domain URL for redirect.
Use https protocol.

Examples:
    get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
    get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
    get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

@param target: The target URL string.
@param domain: The domain string, without protocol.

@return The URL string for redirect.
*/
std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Ensure the target URL starts with https
    if (target.substr(0, 5) != "https") {
        return "https://" + domain;
    }

    // Regex to match the domain and subdomains
    std::regex domain_regex("^https://([\w-]+\.)*" + std::regex_replace(domain, std::regex("\."), "\\.") + "(/.*)?$");

    // Check if the target URL matches the domain
    if (std::regex_match(target, domain_regex)) {
        return target;
    }

    // Fallback to the domain URL
    return "https://" + domain;
}

int main() {
    // Test cases
    std::cout << get_target_for_redirect("https://music.example.com", "example.com") << std::endl;
    std::cout << get_target_for_redirect("https://example.com/service", "example.com") << std::endl;
    std::cout << get_target_for_redirect("https://blog.example.com/posts", "example.com") << std::endl;
    std::cout << get_target_for_redirect("https://another.com", "example.com") << std::endl;
    return 0;
}