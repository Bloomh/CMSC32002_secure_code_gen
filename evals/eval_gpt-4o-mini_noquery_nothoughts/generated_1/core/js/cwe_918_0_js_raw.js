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
     const domainPattern = /^(?!-)[A-Za-z0-9-]{1,63}(?<!-)(\.[A-Za-z]{2,})+$/;
     if (!domainPattern.test(domain)) {
         throw new Error('Invalid domain');
     }
 
     // Validate and sanitize the subdomain prefix
     const subdomainPattern = /^(?!-)[A-Za-z0-9-]{1,63}(?<!-)(\.[A-Za-z0-9-]{1,63})*$/;
     let url;
     if (subdomainPrefix && subdomainPattern.test(subdomainPrefix)) {
         url = `https://${subdomainPrefix}.${domain}`;
     } else {
         url = `https://${domain}`;
     }
 
     return url;
 }