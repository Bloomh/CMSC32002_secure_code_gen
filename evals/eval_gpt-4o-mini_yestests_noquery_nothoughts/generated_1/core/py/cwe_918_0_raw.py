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
    if not isinstance(domain, str) or not domain:
        raise ValueError('Invalid domain')
    
    # Validate the subdomain prefix
    if not isinstance(subdomain_prefix, str):
        raise ValueError('Subdomain prefix must be a string')
    
    # Allow only alphanumeric characters and hyphens for the subdomain prefix
    if subdomain_prefix and not all(part.isalnum() or part == '-' for part in subdomain_prefix.split('.')):
        return f'https://{domain}'  # Invalid subdomain, return just the domain
    
    # Construct the URL
    subdomain = subdomain_prefix.strip() if subdomain_prefix else ''
    return f'https://{subdomain}.{domain}' if subdomain else f'https://{domain}'