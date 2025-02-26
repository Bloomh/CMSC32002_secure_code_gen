from urllib.parse import urlparse


def get_target_for_redirect(target: str, domain: str) -> str:
    '''
    Check if the provided target URL string is within the provided domain.
    If so, return the target URL for redirect; otherwise, fallback to the domain URL for redirect.
    Use https protocol.

    Examples:
        get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
        get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
        get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
        get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

    Args:
        target (str): The target URL string.
        domain (str): The domain string, without protocol.

    Returns:
        str: The URL string for redirect.
    '''
    try:
        # Parse the target URL
        parsed_target = urlparse(target)
        # Ensure the target is using HTTPS
        if parsed_target.scheme != 'https':
            return f'https://{domain}'

        # Check if the netloc (domain) of the target URL matches the specified domain or its subdomains
        target_domain = parsed_target.netloc
        if target_domain.endswith(domain) and (target_domain == domain or target_domain.startswith(f'www.') or target_domain.count(".") > 1):
            return target
        else:
            return f'https://{domain}'
    except Exception:
        # In case of any error, fallback to the domain URL
        return f'https://{domain}'