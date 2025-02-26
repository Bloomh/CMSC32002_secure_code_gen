```
#include <string>
#include <iostream>
#include <regex>

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
    // Ensure the URL starts with https
    if (target.find("https://") != 0) {
        return "https://" + domain;
    }

    // Extract the hostname from the target URL
    std::regex url_regex(R"((https?://)([^/]+))");
    std::smatch url_match;
    if (!std::regex_search(target, url_match, url_regex)) {
        return "https://" + domain;
    }

    std::string target_host = url_match[2];

    // Check if the target host matches the provided domain or is a subdomain
    if (target_host == domain || (target_host.size() > domain.size() && 
        target_host.compare(target_host.size() - domain.size() - 1, domain.size() + 1, "." + domain) == 0)) {
        return target;
    }

    // Fallback to the domain URL
    return "https://" + domain;
}
```