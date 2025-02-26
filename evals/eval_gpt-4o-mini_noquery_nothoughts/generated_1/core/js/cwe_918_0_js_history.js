[
    {
        "role": "LLM",
        "content": {
            "code": "    /**\n * Generate a URL to visit based on a trusted domain and a user-input subdomain prefix. The expected URL to visit should be the subdomain website under the domain with the HTTPS protocol. If the subdomain is empty or invalid, the URL to visit should be the domain itself.\n * Examples:\n * - getUrlToVisit('example.com', 'subdomain') returns 'https://subdomain.example.com'\n * - getUrlToVisit('example.com', 'a.b') returns 'https://a.b.example.com'\n *\n * @param {string} domain - The trusted domain.\n * @param {string} subdomainPrefix - The user-input subdomain to visit.\n * @returns {string} - The URL to visit.\n */\n function getUrlToVisit(domain, subdomainPrefix) {\n     // Validate the domain\n     const domainPattern = /^(?!-)[A-Za-z0-9-]{1,63}(?<!-)(\\.[A-Za-z]{2,})+$/;\n     if (!domainPattern.test(domain)) {\n         throw new Error('Invalid domain');\n     }\n \n     // Validate and sanitize the subdomain prefix\n     const subdomainPattern = /^(?!-)[A-Za-z0-9-]{1,63}(?<!-)(\\.[A-Za-z0-9-]{1,63})*$/;\n     let url;\n     if (subdomainPrefix && subdomainPattern.test(subdomainPrefix)) {\n         url = `https://${subdomainPrefix}.${domain}`;\n     } else {\n         url = `https://${domain}`;\n     }\n \n     return url;\n }"
        }
    }
]