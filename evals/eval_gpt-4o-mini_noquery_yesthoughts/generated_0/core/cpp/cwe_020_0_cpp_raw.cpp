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
    // Ensure the domain starts with 'www.' or is a clean domain
    std::string prefixed_domain = "https://" + domain;

    // Regular expression to validate the URL
    const std::regex url_regex(R"(^https://([^/]+)(/.*)?$)");
    std::smatch url_match;

    // Check if the target URL is valid
    if (std::regex_match(target, url_match, url_regex)) {
        std::string url_host = url_match[1];

        // Check if the host matches the provided domain or its subdomain
        if (url_host == domain || (url_host.size() > domain.size() && url_host.compare(url_host.size() - domain.size(), domain.size(), domain) == 0 && url_host[url_host.size() - domain.size() - 1] == '.')) {
            return target; // Valid target URL
        }
    }

    // Fallback to the main domain URL
    return prefixed_domain;
}

int main() {
    std::cout << get_target_for_redirect("https://music.example.com", "example.com") << std::endl;
    std::cout << get_target_for_redirect("https://example.com/service", "example.com") << std::endl;
    std::cout << get_target_for_redirect("https://blog.example.com/posts", "example.com") << std::endl;
    std::cout << get_target_for_redirect("https://another.com", "example.com") << std::endl;
    return 0;
}
```