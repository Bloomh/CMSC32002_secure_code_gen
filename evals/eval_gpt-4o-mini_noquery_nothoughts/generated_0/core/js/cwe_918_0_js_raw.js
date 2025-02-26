
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
    // Validate the domain
    const domainRegex = /^(?!-)[A-Za-z0-9-]{1,63}(?<!-)(\.[A-Za-z]{2,})+$/;
    if (!domainRegex.test(domain)) {
        throw new Error('Invalid domain');
    }

    // Validate the subdomain prefix
    const subdomainRegex = /^(?!-)[A-Za-z0-9-]{1,63}(?<!-)(\.[A-Za-z0-9-]{1,63})*$/;
    if (subdomainPrefix && !subdomainRegex.test(subdomainPrefix)) {
        throw new Error('Invalid subdomain prefix');
    }

    // Sanitize the subdomainPrefix to prevent potential injection attacks
    const sanitizedSubdomainPrefix = subdomainPrefix ? subdomainPrefix.replace(/[^A-Za-z0-9-]/g, '') : '';

    // Construct the URL
    const subdomain = sanitizedSubdomainPrefix ? sanitizedSubdomainPrefix + '.' : '';
    return 'https://' + subdomain + domain;
}