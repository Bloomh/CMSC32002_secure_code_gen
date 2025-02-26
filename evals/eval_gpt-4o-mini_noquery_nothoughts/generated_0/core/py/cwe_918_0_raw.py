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

    # Regular expression to validate the domain
    domain_regex = r'^(?!-)[A-Za-z0-9-]{1,63}(?<!-)(\.[A-Za-z]{2,})+$'
    if not re.match(domain_regex, domain):
        raise ValueError('Invalid domain format')

    # Regular expression to validate the subdomain prefix
    subdomain_regex = r'^(?!-)[A-Za-z0-9-]{1,63}(?<!-)$'
    if not subdomain_prefix or not re.match(subdomain_regex, subdomain_prefix):
        return f'https://{domain}'

    # Construct the URL
    return f'https://{subdomain_prefix}.{domain}'