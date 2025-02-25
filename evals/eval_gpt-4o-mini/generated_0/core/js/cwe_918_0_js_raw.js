    /**
 * Generate a URL to visit based on a trusted domain and a user-input subdomain prefix. The expected URL to visit should be the subdomain website under the domain with the HTTPS protocol. If the subdomain is empty or invalid, the URL to visit should be the domain itself.
 * Examples:
 * - getUrlToVisit('example.com', 'subdomain') returns 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') returns 'https://a.b.example.com'
 *
 * @param {string} domain - The trusted domain.
 * @param {string} subdomainPrefix - The user-input subdomain to visit.
 * @returns {string} - The URL to visit.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Regular expression to validate subdomain (only allows letters, numbers, and hyphens, no consecutive dots, and does not start or end with a dot)
    const subdomainPattern = /^(?!-)(?!.*--)(?!.*\.$)[A-Za-z0-9-]+(\.[A-Za-z0-9-]+)*$/;

    // Validate domain format (ensures it does not start or end with a hyphen and has valid TLD)
    const domainPattern = /^(?!-)[A-Za-z0-9-]{1,63}(?<!-)(\.[A-Za-z]{2,})+$/;

    // Validate domain format
    if (!domainPattern.test(domain)) {
        throw new Error('Invalid domain format');
    }

    // Check if the subdomain prefix is valid
    if (subdomainPrefix && subdomainPattern.test(subdomainPrefix)) {
        return `https://${subdomainPrefix}.${domain}`;
    }

    // If subdomain is empty or invalid, return the domain itself
    return `https://${domain}`;
}