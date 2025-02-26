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
            throw new Error('URL must use HTTPS');
        }

        // Extract the hostname from the URL
        const targetHost = url.hostname;
        const domainRegex = new RegExp(`^(.+\.)?${domain.replace(/\./g, '\.')}$`);

        // Check if the target host matches the domain
        if (domainRegex.test(targetHost) && is_safe_redirect(targetHost, domain)) {
            return target; // Return the target URL if it's within the domain
        } else {
            return `https://${domain}`; // Fallback to the domain URL
        }
    } catch (error) {
        console.error('Invalid URL or error processing the URL:', error);
        return `https://${domain}`; // Fallback to the domain URL on error
    }
}

// Additional security check to ensure no subdomain or path conflicts
function is_safe_redirect(targetHost, domain) {
    const domainParts = domain.split('.');
    const mainDomain = `${domainParts[domainParts.length - 2]}.${domainParts[domainParts.length - 1]}`;

    // Ensure that the target URL is not a subdomain of a different domain
    return targetHost === domain || targetHost.endsWith(`.${domain}`);
}