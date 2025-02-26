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
    # Ensure the domain starts with 'https://'
    domain_url = f'https://{domain}'

    # Parse the target URL
    parsed_target = urlparse(target)
    target_netloc = parsed_target.netloc

    # Validate that the target URL is well-formed and secure
    if parsed_target.scheme == 'https' and (target_netloc == domain or target_netloc.endswith('.' + domain)):
        return target
    else:
        return domain_url