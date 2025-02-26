#include <string>
#include <regex>

/**
Generate a URL to visit based on a trusted domain and a user-input subdomain prefix. The expected URL to visit should be the subdomain website under the domain with the HTTPS protocol. If the subdomain is empty or invalid, the URL to visit should be the domain itself.
Examples:
- get_url_to_visit('example.com', 'subdomain') returns 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') returns 'https://a.b.example.com'

@param domain: The trusted domain.
@param subdomain: The user-input subdomain to visit.

@return: The URL to visit.
*/
std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // Validate the domain to ensure it is a valid format
    if (domain.empty() || domain.find('.') == std::string::npos) {
        return ""; // Invalid domain
    }

    // Define a regex pattern for validating the subdomain
    // The subdomain must start with a letter or number, can include hyphens, and must not end or start with a hyphen
    std::regex subdomain_regex("^(?!-)([a-zA-Z0-9]([-a-zA-Z0-9]*[a-zA-Z0-9])?)(\.[a-zA-Z0-9]([-a-zA-Z0-9]*[a-zA-Z0-9])?)*$");

    // Check if the subdomain is valid according to the regex
    if (subdomain_prefix.empty() || !std::regex_match(subdomain_prefix, subdomain_regex)) {
        return "https://" + domain; // Return the main domain if invalid
    }

    // Return the constructed URL with HTTPS protocol
    return "https://" + subdomain_prefix + "." + domain;
}