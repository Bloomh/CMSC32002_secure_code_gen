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
        raise ValueError('Invalid domain provided.')

    # Validate the subdomain prefix
    if not isinstance(subdomain_prefix, str):
        raise ValueError('Subdomain prefix must be a string.')

    # Allow only valid characters in subdomain prefix
    if subdomain_prefix and not all(c.isalnum() or c in ['-', '.'] for c in subdomain_prefix):
        raise ValueError('Subdomain prefix contains invalid characters.')
    if subdomain_prefix.startswith('-') or subdomain_prefix.endswith('-'):
        raise ValueError('Subdomain prefix cannot start or end with a hyphen.')
    if subdomain_prefix.startswith('.') or subdomain_prefix.endswith('.'):  
        raise ValueError('Subdomain prefix cannot start or end with a dot.')

    # Prevent potential open redirect by ensuring subdomain is a valid format
    valid_subdomain = subdomain_prefix.split('.')
    if len(valid_subdomain) > 2:
        raise ValueError('Subdomain prefix cannot contain more than two parts.')

    # Construct the URL
    return f'https://{subdomain_prefix}.{domain}' if subdomain_prefix else f'https://{domain}'