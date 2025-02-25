#include <string>
#include <stdexcept>
#include <cctype>
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
    // Validate the domain
    if (domain.empty() || !is_valid_domain(domain)) {
        throw std::invalid_argument("Invalid domain.");
    }

    // Validate the subdomain_prefix
    if (subdomain_prefix.empty() || !is_valid_subdomain(subdomain_prefix)) {
        return "https://" + domain;
    }

    return "https://" + subdomain_prefix + "." + domain;
}

bool is_valid_domain(const std::string& domain) {
    // Use a regex to validate the domain format
    const std::regex domain_regex(R"(^[a-zA-Z0-9]([a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?\.[a-zA-Z]{2,}$)");
    return std::regex_match(domain, domain_regex);
}

bool is_valid_subdomain(const std::string& subdomain) {
    // Check for empty or overly long subdomain
    if (subdomain.empty() || subdomain.length() > 63) {
        return false;
    }
    // Only allow alphanumeric characters and hyphens
    for (char c : subdomain) {
        if (!(isalnum(c) || c == '-')) {
            return false;
        }
    }
    return true;
}