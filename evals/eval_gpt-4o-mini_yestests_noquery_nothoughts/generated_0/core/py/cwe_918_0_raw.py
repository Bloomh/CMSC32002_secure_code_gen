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
        subdomain_prefix = ''
    subdomain_prefix = subdomain_prefix.strip()
    
    # Check if the subdomain prefix is empty
    if not subdomain_prefix:
        return f'https://{domain}'
    
    # Check for invalid characters in the subdomain prefix
    if not all(c.isalnum() or c in ['-', '_'] for c in subdomain_prefix) or 
       subdomain_prefix.startswith('-') or subdomain_prefix.endswith('-') or 
       '..' in subdomain_prefix or 
       any(c in subdomain_prefix for c in ['/', '#', '?']):
        return f'https://{domain}'
    
    # Construct the URL
    return f'https://{subdomain_prefix}.{domain}'