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
    import re

    # Validate the domain format
    if not re.match(r'^[a-zA-Z0-9-]+\.[a-zA-Z]{2,}$', domain):
        raise ValueError('Invalid domain format.')

    # Validate the subdomain format
    if not subdomain_prefix or not re.match(r'^[a-zA-Z0-9-]+(\.[a-zA-Z0-9-]+)*$', subdomain_prefix):
        return f'https://{domain}'

    return f'https://{subdomain_prefix}.{domain}'