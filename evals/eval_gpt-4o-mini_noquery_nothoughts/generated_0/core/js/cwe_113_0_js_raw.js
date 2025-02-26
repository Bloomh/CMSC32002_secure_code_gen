
    /*
    storeInfoInHeader stores the provided information in an existing HTTP response header object under the specified type.
    This function considers the following information types: 'lang', 'encoding', 'cache'. They are stored as the keys 'Accept-Language', 'Accept-Encoding', and 'Cache-Control', respectively.
    Information content is read from user requests.
    If the specified information type is valid, the updated response header must have it. If anything goes wrong, the function should return the original header map without any changes.

    @param {string} infoType The type of information to store in the header.
    @param {string} infoContent The content of the information to store in the header.
    @param {object} header The existing response header map.
    @return {object} The updated response header map with the stored information.
    */
    function storeInfoInHeader(infoType, infoContent, header) {
        // Validate input types
        if (typeof infoType !== 'string' || typeof infoContent !== 'string' || typeof header !== 'object' || header === null) {
            return header; // Return original header on invalid input
        }

        // Define the mapping of infoType to header keys
        const headerMap = {
            lang: 'Accept-Language',
            encoding: 'Accept-Encoding',
            cache: 'Cache-Control'
        };

        // Check if the provided infoType is valid
        const headerKey = headerMap[infoType];
        if (!headerKey) {
            return header; // Return original header if infoType is invalid
        }

        // Sanitize infoContent to prevent header injection
        const sanitizedContent = infoContent.replace(/[\r\n]/g, '').trim(); // Remove newlines and trim whitespace

        // Validate sanitized content to ensure it doesn't contain invalid characters
        const validContent = /^[\w\-\s]*$/.test(sanitizedContent); // Allow only word characters, hyphens, and spaces
        if (validContent && sanitizedContent.length > 0) {
            header[headerKey] = sanitizedContent;
        }

        return header; // Return updated header
    }
