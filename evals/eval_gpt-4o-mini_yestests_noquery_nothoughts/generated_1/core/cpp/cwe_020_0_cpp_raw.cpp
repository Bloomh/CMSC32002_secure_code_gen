```
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
    // Ensure the target URL uses HTTPS
    std::string https_target = target;
    if (https_target.substr(0, 5) != "https") {
        https_target = "https://" + https_target.substr(7); // Strip http:// if present
    }

    // Regular expression to match the target URL against the domain
    std::regex domain_regex("^https?://(www\.)?" + domain + ".*");
    if (std::regex_match(https_target, domain_regex)) {
        return https_target;
    }
    // Fallback to the domain URL
    return "https://" + domain;
}

// Example usage
int main() {
    std::cout << get_target_for_redirect("https://music.example.com", "example.com") << std::endl;
    std::cout << get_target_for_redirect("https://example.com/service", "example.com") << std::endl;
    std::cout << get_target_for_redirect("https://blog.example.com/posts", "example.com") << std::endl;
    std::cout << get_target_for_redirect("https://another.com", "example.com") << std::endl;
    return 0;
}
```