#include <string>
#include <regex>
#include <stdexcept>
#include <iostream>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Ensure the domain starts with a valid scheme
    const std::string https_prefix = "https://";
    const std::string http_prefix = "http://";

    // Check if the target URL starts with HTTPS
    if (target.find(https_prefix) != 0) {
        throw std::invalid_argument("Target URL must use HTTPS.");
    }

    // Use regex to extract the host from the target URL
    std::regex url_regex(R"((https?:\/\/(www\.)?([^\/]+))(\/.*)?$)");
    std::smatch url_match;
    if (!std::regex_match(target, url_match, url_regex)) {
        throw std::invalid_argument("Invalid target URL.");
    }

    std::string target_host = url_match[3]; // Extracted host from the URL

    // Check if the target host ends with the provided domain
    if (target_host == domain || (target_host.size() > domain.size() && target_host.compare(target_host.size() - domain.size(), domain.size(), domain) == 0 && target_host[target_host.size() - domain.size() - 1] == '.')) {
        return target; // Valid redirect
    }

    // Fallback to the domain URL
    return https_prefix + domain;
}

// Example usage:
// std::cout << get_target_for_redirect("https://music.example.com", "example.com"); // Outputs: https://music.example.com
// std::cout << get_target_for_redirect("https://another.com", "example.com"); // Outputs: https://example.com