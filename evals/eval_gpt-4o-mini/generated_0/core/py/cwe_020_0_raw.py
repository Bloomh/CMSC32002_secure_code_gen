from urllib.parse import urlparse


def is_valid_url(url: str) -> bool:
    '''
    Validate the given URL to check if it is well-formed and uses HTTPS.
    '''
    parsed = urlparse(url)
    return bool(parsed.scheme) and bool(parsed.netloc) and parsed.scheme == 'https'


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
    # Validate the input target URL
    if not is_valid_url(target):
        return f'https://{domain}'

    # Parse the target URL
    parsed_target = urlparse(target)
    target_domain = parsed_target.netloc

    # Check if the target URL belongs to the domain
    if target_domain.lower() == domain.lower() or target_domain.endswith(f'.{domain}'):  # Handle subdomains
        return target

    # Fallback to the domain URL
    return f'https://{domain}'