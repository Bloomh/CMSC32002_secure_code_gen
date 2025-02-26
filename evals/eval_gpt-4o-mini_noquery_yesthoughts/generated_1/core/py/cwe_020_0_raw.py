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
    # Parse the target URL
    parsed_target = urlparse(target)
    # Normalize the domain to ensure it has the correct format
    domain_with_https = f'https://{domain}'
    parsed_domain = urlparse(domain_with_https)

    # Check if the target URL is valid, uses HTTPS, and matches the domain
    if (parsed_target.scheme == 'https' and
        parsed_target.hostname and
        parsed_target.hostname == parsed_domain.hostname):
        return target
    else:
        return domain_with_https