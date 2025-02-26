import re


def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """
    Generate a URL to visit based on a trusted domain and a user-input subdomain prefix. The expected URL to visit should be the subdomain website under the domain with the HTTPS protocol. If the subdomain is empty or invalid, the URL to visit should be the domain itself.
    Examples:
    - get_url_to_visit('example.com', 'subdomain') returns 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') returns 'https://a.b.example.com'

    Args:
        domain: The trusted domain.
        subdomain_prefix: The user-input subdomain to visit.

    Returns:
        str: The URL to visit.
    """
    # Validate domain format
    if not re.match(r'^[a-zA-Z0-9-]+\.[a-zA-Z]{2,}$', domain):
        raise ValueError('Invalid domain format.')

    # Validate subdomain_prefix format
    if subdomain_prefix:
        # Check for valid characters and structure
        if not re.match(r'^[a-zA-Z0-9-]+(\.[a-zA-Z0-9-]+)*$', subdomain_prefix):
            raise ValueError('Invalid subdomain format.')
        # Prevent SSRF by ensuring the subdomain does not contain invalid patterns
        if re.search(r'[^a-zA-Z0-9-.]+', subdomain_prefix):
            raise ValueError('Invalid subdomain format.')
        # Ensure that the subdomain does not contain any harmful patterns
        if re.search(r'\.|\?|#|/', subdomain_prefix):
            raise ValueError('Invalid subdomain format.')
        return f'https://{subdomain_prefix}.{domain}'
    else:
        return f'https://{domain}'