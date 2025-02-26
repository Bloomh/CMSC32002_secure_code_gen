```
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
    const validTypes = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    const headerKey = validTypes[infoType];

    // If the infoType is not valid, return the original header
    if (!headerKey) {
        return header;
    }

    // Sanitize the infoContent to prevent header injection attacks
    const sanitizedContent = infoContent.replace(/[^a-zA-Z0-9,;\s-]/g, '').trim();

    // Check if the sanitized content is empty after sanitization
    if (!sanitizedContent) {
        return header;
    }

    // Update the header with the sanitized content
    header[headerKey] = sanitizedContent;

    return header;
}
```