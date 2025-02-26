```
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
    // Validate the domain using a regex pattern
    const std::regex domain_regex(R"(^[a-zA-Z0-9][-a-zA-Z0-9]{0,61}[a-zA-Z0-9]\.[a-zA-Z]{2,}$)");
    const std::regex subdomain_regex(R"(^[a-zA-Z0-9]([-a-zA-Z0-9]{0,61}[a-zA-Z0-9])?$)");
    std::string url;

    // Check if the domain is valid and non-empty
    if (domain.empty() || !std::regex_match(domain, domain_regex)) {
        return ""; // Return an empty string if the domain is invalid
    }

    // If subdomain prefix is valid, construct the URL with subdomain
    if (!subdomain_prefix.empty() && std::regex_match(subdomain_prefix, subdomain_regex)) {
        url = "https://" + subdomain_prefix + "." + domain;
    } else {
        // If invalid or empty, return the domain itself
        url = "https://" + domain;
    }

    return url;
}
```