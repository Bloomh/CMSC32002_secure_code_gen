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
    // Define a mapping of valid info types to their corresponding header keys
    const headerKeys = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    // Validate the infoType and ensure it's a string
    const headerKey = headerKeys[infoType];
    if (headerKey && typeof infoContent === 'string') {
        // Sanitize infoContent to prevent header injection and ensure valid format
        const sanitizedContent = infoContent
            .replace(/[^\w\s,-;=]/g, '') // Allow only valid characters
            .replace(/\n/g, '') // Remove newlines
            .replace(/\r/g, ''); // Remove carriage returns

        // Check if the sanitized content is valid after sanitization
        if (sanitizedContent.length > 0) {
            // Update the header with the sanitized content
            header[headerKey] = sanitizedContent;
        }
        return header;
    }
    // Return original header if validation fails
    return header;
}