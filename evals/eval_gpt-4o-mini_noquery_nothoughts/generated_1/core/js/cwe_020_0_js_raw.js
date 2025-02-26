
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
        // Ensure the target URL uses HTTPS
        const url = new URL(target);
        if (url.protocol !== 'https:') {
            throw new Error('Invalid protocol');
        }

        // Normalize the domain to ensure it is in the correct format
        const normalizedDomain = domain.toLowerCase().trim();
        const domainPattern = new RegExp(`(\.|^)${normalizedDomain.replace(/([.*+?^=!:${}()|[\\]])/g, '\\$1')}$`);

        // Validate the target hostname against the provided domain
        if (domainPattern.test(url.hostname.toLowerCase())) {
            return target; // Return the original target URL
        } else {
            return `https://${normalizedDomain}`; // Fallback to the domain URL
        }
    } catch (error) {
        // In case of an error, log it and fallback to the domain
        console.error('Error processing URL:', error);
        return `https://${domain}`;
    }
}