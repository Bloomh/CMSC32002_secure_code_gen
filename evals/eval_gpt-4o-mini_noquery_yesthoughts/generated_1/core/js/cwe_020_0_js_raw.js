    /**
 * Check if the provided target URL string is within the provided domain.
 * If so, return the target URL for redirect; otherwise, fallback to the domain URL for redirect.
 * Use https protocol.
 *
 * Examples:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - The target URL string.
 * @param {string} domain - The domain string, without protocol.
 * @returns {string} The URL string for redirect.
 */
function get_target_for_redirect(target, domain) {
    // Validate input parameters
    if (typeof target !== 'string' || typeof domain !== 'string') {
        throw new Error('Invalid input: target and domain must be strings.');
    }

    try {
        // Ensure the target URL uses HTTPS
        const url = new URL(target);
        if (url.protocol !== 'https:') {
            throw new Error('URL must use HTTPS protocol.');
        }

        // Create a regex to match the domain and its subdomains
        const domainPattern = new RegExp(`^https://(www\.)?(${domain.replace(/\./g, '\.')})(/|$)`);

        // If the target URL matches the domain, return it
        if (domainPattern.test(url.href)) {
            return url.href;
        }
    } catch (error) {
        console.error('Error processing URL:', error);
        // Handle invalid URL format
    }

    // Fallback to the domain URL
    return `https://${domain}`;
}