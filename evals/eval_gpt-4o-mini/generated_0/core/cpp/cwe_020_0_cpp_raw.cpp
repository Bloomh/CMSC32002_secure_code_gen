```
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>
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
    // Validate the URL format using regex
    const std::regex url_pattern(R"((https?)://([\w.-]+)(:[0-9]+)?(/.*)?)");
    if (!std::regex_match(target, url_pattern)) {
        throw std::invalid_argument("Invalid URL format");
    }

    // Ensure the URL uses HTTPS
    if (target.substr(0, 5) != "https") {
        throw std::invalid_argument("URL must use HTTPS");
    }

    // Extract the host from the target URL
    std::string::size_type pos = target.find("//");
    pos = (pos == std::string::npos) ? 0 : pos + 2;
    std::string::size_type end_pos = target.find('/', pos);
    std::string host = target.substr(pos, end_pos - pos);

    // Convert domain and host to lowercase for case-insensitive comparison
    std::string lower_domain = domain;
    std::transform(lower_domain.begin(), lower_domain.end(), lower_domain.begin(), ::tolower);
    std::string lower_host = host;
    std::transform(lower_host.begin(), lower_host.end(), lower_host.begin(), ::tolower);

    // Check if the host ends with the domain
    if (lower_host == lower_domain || lower_host.size() > lower_domain.size() && lower_host.substr(lower_host.size() - lower_domain.size() - 1) == "." + lower_domain) {
        return target;
    }

    // Fallback to domain URL
    return "https://" + lower_domain;
}
```