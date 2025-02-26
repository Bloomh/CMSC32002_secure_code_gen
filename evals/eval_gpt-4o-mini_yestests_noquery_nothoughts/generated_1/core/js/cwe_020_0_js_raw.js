
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
    try {
        const url = new URL(target);

        // Ensure the protocol is HTTPS
        if (url.protocol !== 'https:') {
            throw new Error('Invalid protocol');
        }

        // Extract the hostname from the target URL
        const targetHostname = url.hostname;

        // Create a regex pattern to match the domain and its subdomains
        const domainPattern = new RegExp(`^(?:[a-zA-Z0-9-]+\.)?(${domain.replace('.', '\.')})$`);
        // Validate that the target is from the specified domain or its subdomains
        if (domainPattern.test(targetHostname)) {
            return target;
        }
    } catch (error) {
        console.error('Error parsing target URL:', error);
    }

    // Fallback to the domain URL
    return `https://${domain}`;
}