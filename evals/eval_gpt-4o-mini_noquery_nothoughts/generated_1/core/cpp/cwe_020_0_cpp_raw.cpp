
#include <string>
#include <regex>
#include <stdexcept>
#include <algorithm>
#include <cctype>

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
    // Validate inputs to prevent potential security issues
    if (target.empty() || domain.empty()) {
        throw std::invalid_argument("Target and domain cannot be empty.");
    }

    // Ensure the domain is in a valid format
    std::string domain_lower = domain;
    std::transform(domain_lower.begin(), domain_lower.end(), domain_lower.begin(), ::tolower);

    // Define a regex to match the target URL against the domain
    std::regex domain_regex("^https://([a-zA-Z0-9\-]+\.)*" + domain_lower + "(:\d+)?(/.*)?$");

    // Check if the target URL matches the domain regex
    if (std::regex_match(target, domain_regex)) {
        return target; // Return the target URL if it matches the domain
    }
    // If it does not match, fallback to the domain URL with https
    return "https://" + domain_lower;
}