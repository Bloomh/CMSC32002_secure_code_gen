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
        const urlObj = new URL(target);
        // Ensure the URL uses HTTPS
        if (urlObj.protocol !== 'https:') {
            return `https://${domain}`; // Fallback to domain
        }
        // Validate the domain
        const targetDomain = urlObj.hostname;
        const domainRegex = new RegExp(`^(www\.)?${domain.replace(/\./g, '\\.')}$|^(www\.)?${domain.replace(/\./g, '\\.')}(\.[a-z]{2,})$`);
        if (domainRegex.test(targetDomain)) {
            return target; // Return the original target if valid
        } else {
            return `https://${domain}`; // Fallback to domain
        }
    } catch (error) {
        return `https://${domain}`; // Invalid URL, fallback to domain
    }
}