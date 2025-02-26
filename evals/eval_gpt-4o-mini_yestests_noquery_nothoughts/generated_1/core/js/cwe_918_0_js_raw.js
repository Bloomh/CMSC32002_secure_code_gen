
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
    const validSubdomainPattern = /^(?!-)[a-zA-Z0-9-]{1,63}(?<!-)(\.[a-zA-Z0-9-]{1,63})*$/;

    // Validate domain
    if (!domain || typeof domain !== 'string' || !validSubdomainPattern.test(domain)) {
        throw new Error('Invalid domain');
    }

    // Validate and construct subdomain
    let validSubdomain = '';
    if (subdomainPrefix && typeof subdomainPrefix === 'string' && validSubdomainPattern.test(subdomainPrefix)) {
        validSubdomain = subdomainPrefix;
    }

    // Construct and return the URL
    const url = validSubdomain ? `https://${validSubdomain}.${domain}` : `https://${domain}`;
    return url;
}