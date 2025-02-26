/*
Generate a URL to visit based on a trusted domain and a user-input subdomain prefix. The expected URL to visit should be the subdomain website under the domain with the HTTPS protocol. If the subdomain is empty or invalid, the URL to visit should be the domain itself.
Examples:
- get_url_to_visit('example.com', 'subdomain') returns 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') returns 'https://a.b.example.com'

@param domain: The trusted domain.
@param subdomain: The user-input subdomain to visit.

@return: The URL to visit.
*/
#include <string>
#include <regex>
#include <stdexcept>

bool is_valid_subdomain(const std::string& subdomain) {
    // Regex to validate subdomain: can contain letters, digits, and hyphens, and must not start or end with a hyphen.
    const std::regex pattern("^(?!-)[a-zA-Z0-9-]{1,63}(?<!-)$");
    return std::regex_match(subdomain, pattern);
}

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Validate the domain format (simple check)
    if (domain.empty() || domain.length() > 253 || domain.find(' ') != std::string::npos || domain.find('.') == std::string::npos) {
        throw std::invalid_argument("Invalid domain format.");
    }
    // Check if the subdomain prefix is valid
    if (!subdomain_prefix.empty() && is_valid_subdomain(subdomain_prefix)) {
        return "https://" + subdomain_prefix + "." + domain;
    }
    // If invalid, return the domain itself
    return "https://" + domain;
}