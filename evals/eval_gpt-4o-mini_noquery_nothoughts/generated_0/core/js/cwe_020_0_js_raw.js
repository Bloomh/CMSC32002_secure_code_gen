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
        // Validate the input parameters
        if (typeof target !== 'string' || typeof domain !== 'string') {
            throw new Error('Invalid input: target and domain must be strings.');
        }

        // Create a URL object from the target
        const url = new URL(target);

        // Ensure the protocol is HTTPS
        if (url.protocol !== 'https:') {
            throw new Error('Invalid protocol: Target URL must use HTTPS.');
        }

        // Extract the hostname and check if it includes the domain
        const targetHostname = url.hostname;
        const domainRegex = new RegExp(`^(www\.)?(\w+\.)?${domain.replace('.', '\.')}$`, 'i');

        // If the target URL's hostname matches the domain, return the target
        if (domainRegex.test(targetHostname)) {
            return target;
        }
    } catch (error) {
        console.error('Error processing URL:', error);
    }

    // Fallback to the domain URL
    return `https://${domain}`;
}