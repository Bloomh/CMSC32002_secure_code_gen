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
    # Validate the domain
    if not re.match(r'^[a-z0-9.-]+\.[a-z]{2,}$', domain):
        raise ValueError('Invalid domain format.')

    # Validate and sanitize the subdomain prefix
    if subdomain_prefix:
        if not re.match(r'^[a-z0-9-]+(\.[a-z0-9-]+)*$', subdomain_prefix):
            raise ValueError('Invalid subdomain format.')
        if len(subdomain_prefix) > 63:
            raise ValueError('Subdomain exceeds maximum length of 63 characters.')
        if subdomain_prefix.startswith('.') or subdomain_prefix.endswith('.'):  # Prevent leading/trailing dots
            raise ValueError('Subdomain cannot start or end with a dot.')
        return f'https://{subdomain_prefix}.{domain}'
    else:
        return f'https://{domain}'